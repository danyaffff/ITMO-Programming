#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
unsigned reverse(unsigned size) {
    return ((size >> 24) & 0x000000ff) | ((size >> 8) & 0x0000ff00) | ((size << 8) & 0x00ff0000) | ((size << 24) & 0xff000000);
}
 
typedef union Tag {
    char buffer[12];
    struct {
        unsigned short empty;
        unsigned char version[3];
        unsigned char version_1;
        unsigned char version_2;
        unsigned char flags;
        unsigned size;
    } TagData;
} TagTag;
 
typedef union Frame {
    char buffer[10];
    struct {
        unsigned char name[4];
        unsigned size;
        unsigned short flags;
    } FrameData;
} FrameTag;
 
void copy(FILE * input, FILE * output) {
    int character;
    while ((character = getc(input)) != EOF)
        putc(character, output);
}
 
void show(char * fileName) {
    FILE * file = fopen(fileName, "rb");
    fseek(file, 0, 0);
    TagTag tag;
    fread(tag.buffer + 2, sizeof(char), 10, file);
    unsigned tagSize = reverse(tag.TagData.size);
    printf("%sv%d.%d\n", tag.TagData.version, tag.TagData.version_1, tag.TagData.version_2);
    while (ftell(file) < tagSize + 10) {
        FrameTag frame;
        fread(frame.buffer, sizeof(char), 10, file);
        if (frame.FrameData.name[0] == 0) {
            break;
        }
        printf("%s: ", frame.FrameData.name);
        unsigned frameSize = reverse(frame.FrameData.size);
        unsigned char * frameContent = malloc(sizeof(char) * frameSize);
        fread(frameContent, sizeof(char), frameSize, file);
        for (int i = 0; i < frameSize; ++i) {
            printf("%c", frameContent[i]);
        }
        printf("\n");
        free(frameContent);
    }
    fclose(file);
}
 
void get(char * fileName, char frameName[4]) {
    FILE * file = fopen(fileName, "rb");
    TagTag tag;
    fread(tag.buffer + 2, sizeof(char), 10, file);
    unsigned tagSize = reverse(tag.TagData.size);
    while (ftell(file) < tagSize + 10) {
        FrameTag frame;
        fread(frame.buffer, sizeof(char), 10, file);
        unsigned frameSize = reverse(frame.FrameData.size);
        if (strcmp((char *)frame.FrameData.name, frameName) == 0) {
            printf("%s: ", frame.FrameData.name);
            unsigned char * FrameContent;
            FrameContent = malloc(sizeof(char) * frameSize);
            fread(FrameContent, sizeof(char), frameSize, file);
            for (int i = 0; i < frameSize; i++) {
                printf("%c", FrameContent[i]);
            }
            printf("\n");
            free(FrameContent);
            fclose(file);
            return;
        }
        fseek(file, frameSize, 1);
    }
    fclose(file);
}
 
void set(char * fileName, char frameName[4], char * frameValue) {
    FILE * file = fopen(fileName, "rb");
    TagTag tag;
    fread(tag.buffer + 2, sizeof(char), 10, file);
    unsigned tagSize = reverse(tag.TagData.size);
    unsigned oldFramePosition = 0;
    unsigned oldFrameSize = 0;
    while (ftell(file) < tagSize + 10) {
        FrameTag frame;
        fread(frame.buffer, sizeof(char), 10, file);
        unsigned FrameSize = reverse(frame.FrameData.size);
        if (strcmp((char*)frame.FrameData.name, frameName) == 0) {
            oldFramePosition = (unsigned)ftell(file) - 10;
            oldFrameSize = FrameSize;
            break;
        }
        fseek(file, FrameSize, 1);
    }
    unsigned valueSize = (unsigned)strlen(frameValue);
    unsigned newTagSize = tagSize - oldFrameSize + valueSize + 10 * (oldFramePosition != 0);
    if (oldFramePosition == 0) {
        oldFramePosition = (unsigned)ftell(file);
    }
    if (valueSize == 0) {
        newTagSize -= 10;
    }
    FILE * fileCopy;
    fileCopy = fopen("temp.mp3", "wb");
    fseek(file, 0, 0);
    fseek(fileCopy, 0, 0);
    copy(file, fileCopy);
    fclose(file);
    fclose(fileCopy);
    fileCopy = fopen("temp.mp3", "rb");
    file = fopen(fileName, "wb");
    tag.TagData.size = reverse(newTagSize);
    fwrite(tag.buffer + 2, sizeof(char), 10, file);
    fseek(fileCopy, 10, 0);
    for (int i = 0; i < oldFramePosition - 10; i++) {
        int Char = getc(fileCopy);
        putc(Char, file);
    }
    if (valueSize > 0) {
        FrameTag frame;
        for (int i = 0; i < 4; ++i) {
            frame.FrameData.name[i] = frameName[i];
        }
        frame.FrameData.size = reverse(valueSize);
        frame.FrameData.flags = 0;
        fwrite(frame.buffer, sizeof(char), 10, file);
    }
    fwrite(frameValue, sizeof(char), valueSize, file);
    fseek(fileCopy, oldFramePosition + 10 + oldFrameSize, 0);
    for (int i = (int)ftell(file); i < newTagSize; i++) {
        int character = getc(fileCopy);
        putc(character, file);
    }
    printf("Новое значение для поля %s: %s\n", frameName, frameValue);
    copy(fileCopy, file);
    fclose(file);
    fclose(fileCopy);
    remove("temp.mp3");
}
 
int main(int argc, char *argv[]) {
    char * fileName = NULL;
    char * frameName = NULL;
    char * value = NULL;
    char showFlag = 0;
    char setFlag = 0;
    char getFlag = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--show") == 0) {
            showFlag = 1;
            continue;
        }
        if (argv[i][2] == 'f')
            fileName = strpbrk(argv[i], "=") + 1;
        if (argv[i][2] == 'g') {
            getFlag = 1;
            frameName = strpbrk(argv[i], "=") + 1;
            continue;
        }
        if (argv[i][2] == 's') {
            setFlag = 1;
            frameName = strpbrk(argv[i], "=") + 1;
            continue;
        }
        if (argv[i][2] == 'v') {
            value = strpbrk(argv[i], "=") + 1;
            continue;
        }
    }
    if (showFlag) {
        show(fileName);
    }
    if (setFlag) {
        get(fileName, frameName);
    }
    if (setFlag) {
        set(fileName, frameName, value);
    }
}
