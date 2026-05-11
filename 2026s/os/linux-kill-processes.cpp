extern "C" {
    #include <fcntl.h>
    #include <unistd.h>
    #include <signal.h>
    #include <sys/syscall.h>
}
#define END_OF_LINE  '\0'
#define BUFFER_SIZE  1024
#define PATH_LENGTH  256
#define SUCCESS       0
#define START         0
#define FAIL          1
const char *processDirectory = "/proc";
int processDirectoryFileDescriptor = -1;
struct linux_dirent64 {
    unsigned long long d_ino;
    long long          d_off;
    unsigned short     d_reclen;
    unsigned char      d_type;
    char               d_name[1];
};
void appendString(char* destination, int& offset, const char* stringToAppend) {
    for (int i = START; stringToAppend[i] != END_OF_LINE; i++)
        destination[offset++] = stringToAppend[i];
    destination[offset] = END_OF_LINE;
}
bool initializedProcessDirectory() {
    processDirectoryFileDescriptor = openat(AT_FDCWD, processDirectory, O_RDONLY | O_DIRECTORY);
    return (processDirectoryFileDescriptor >= START);
}
int getLength(const char* str) {
    int len = START; while (str[len] != END_OF_LINE) { ++len; }
    return len;
}
int parsePIDToInt(const char* str) {
    int processIdentifier = START;
    for (int i = START; str[i] >= '0' and str[i] <= '9'; ++i)
        processIdentifier = (processIdentifier * 10) + (str[i] - '0');
    return processIdentifier;
}
bool directoryIsAProcess(const char* nameOfFolder) {
    return (nameOfFolder[START] >= '1' and nameOfFolder[START] <= '9');
}
void buildCommandFilePath(const char* pidStr, char* outBuffer) {
    int offset = START;
    appendString(outBuffer, offset, processDirectory);
    outBuffer[offset++] = '/';
    appendString(outBuffer, offset, pidStr);
    appendString(outBuffer, offset, "/comm");
}
int readCommandNameFromFile(const char* filePath, char* outputName, int maxBufferSize) {
    int fileDescriptor = openat(AT_FDCWD, filePath, O_RDONLY);
    if (fileDescriptor < START) return -1;
    int bytesRead = read(fileDescriptor, outputName, maxBufferSize - 1);
    close(fileDescriptor);
    if (bytesRead > START) {
        if (outputName[bytesRead - 1] == '\n') bytesRead--;
        outputName[bytesRead] = END_OF_LINE;
    }
    return bytesRead;
}
bool nameContainsTarget(const char* processName, int processLength, const char* targetName, int targetLength) {
    if (targetLength == START or processLength < targetLength) return false;
    for (int i = START; i <= processLength - targetLength; i++) {
        bool isMatch = true;
        for (int j = START; j < targetLength; j++) {
            if (processName[i + j] != targetName[j]) {
                isMatch = false;
                break;
            }
        }
        if (isMatch) return true;
    }
    return false;
}
int killAllMatchingProcesses(const char* targetName) {
    char directoryBuffer[BUFFER_SIZE];
    int targetLength = getLength(targetName);

    while (!SUCCESS) {
        int bytesRead = syscall(SYS_getdents64, processDirectoryFileDescriptor, directoryBuffer, sizeof(directoryBuffer));
        if (bytesRead <= START) break;

        for (int bufferPosition = START; bufferPosition < bytesRead;) {
            struct linux_dirent64* directoryEntry = (struct linux_dirent64*)(directoryBuffer + bufferPosition);

            if (directoryIsAProcess(directoryEntry->d_name)) {
                char commandPath[PATH_LENGTH], commandName[PATH_LENGTH]; buildCommandFilePath(directoryEntry->d_name, commandPath);
                int nameLength = readCommandNameFromFile(commandPath, commandName, sizeof(commandName));

                if ((nameLength > START) and nameContainsTarget(commandName, nameLength, targetName, targetLength)) {
                    const int processIdentifier = parsePIDToInt(directoryEntry->d_name);
                    if (processIdentifier > START)
                        kill(processIdentifier, SIGKILL);
                }
            }
            bufferPosition += directoryEntry->d_reclen;
        }
    }
    close(processDirectoryFileDescriptor);
    return SUCCESS;
}

int main (int n, char** args) { if ((n != 2) or !initializedProcessDirectory()) return FAIL;
    return killAllMatchingProcesses(args[1]);;
}