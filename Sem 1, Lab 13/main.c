/* Лабораторная работа №13. Редактор метаинформации mp3-файла.
 Реализовать редактор текстовой метаинформации mp3 файла. В качестве стандарта метаинформации принимаем ID3v2.
 Редактор представлять из себя консольную программу, принимающую в качестве аргументов имя файла через параметр --filepath, а также одну из выбранных команд

 --show - отображение всей метаинформации в виде таблицы

 --set=prop_name --value=prop_value — выставляет значение определенного поля метаинформации с именем prop_name в значение prop_value

 --get=prop_name - вывести определенное поле метаинформации с именем prop_name */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
unsigned int Reverse(unsigned int Size) { // Реверс
    return ((Size >> 24) & 0x000000ff) | ((Size >> 8) & 0x0000ff00) | ((Size << 8) & 0x00ff0000) | ((Size << 24) & 0xff000000);
}
 
typedef union Tag { // ВОТ ОТ СЮДА
    char Buffer[12]; // строка, по смещению которой мы сможем читать то или иное поле структуры
    struct TagData{
        unsigned short int Empty; // ансигнед шорт инт
        unsigned char Version[3]; // ансигнед чар (строка)
        unsigned char Version_1; // еще один ансигнед чар
        unsigned char Version_2; // все еще ансигнед час
        unsigned char Flags; // такой же ансигнед чар, как и все остальные
        unsigned int Size; // ансигнед инт, что-то новенькое
    } TagData; // имя структуры
} TagTag; // И ВОТ ДО СЮДА У НАС ОПРЕДЕЛЯЕТСЯ НОВЫЙ UNION (typedef) С ИМЕНЕМ TagTag, ЧТОБЫ НЕ ПИСАТЬ КАЖДЫЙ РАЗ union <название_объединения>
 
typedef union Frame { // ВОТ ОТ СЮДА
    char Buffer[10]; // строка для тех же нужд, что и строка в первом union
    struct FrameData{
        unsigned char Name[4]; // ансигнед чар (строка)
        unsigned int Size; // ансигнед инт
        unsigned short int Flags; // короткий беззнаковый инт
    } FrameData; // имя структуры
} FrameTag; // И ДО СЮДА У НАС ОПРЕДЕЛЯЕТСЯ ДРУГОЙ UNION ДЛЯ ТЕХ ЖЕ ПРИЧИН, ЧТО И ПЕРВЫЙ UNION
 
void Copy(FILE *Input, FILE *Output) { // функция copy с аргументами что надо копировать и куда надо копировать
    int Char;
    while ((Char = getc(Input)) != EOF) { // читаем по одному символу, пока не конец файла
        putc(Char, Output); // запихиваем прочитанный символ в выходной файл
    }
}
    
    
 
void Show(char *FileName) {
    FILE* File = fopen(FileName, "rb"); // открываем НЕТЕКСТОВЫЙ (для текстового используется просто "r") файл на чтение
    fseek(File, 0, 0); // ставим курсор в начало
    TagTag Tag; // вызываем юнион TagTag
    fread(Tag.Buffer + 2, sizeof(char), 10, File); // считываем из File 10 объектов длины char и запихиываем в буфер тэга, начиная со 2 байта
    unsigned int TagSize = Reverse(Tag.TagData.Size); // делаем реверс с помощью маски
    printf("%sv%d.%d\n", Tag.TagData.Version, Tag.TagData.Version_1, Tag.TagData.Version_2); // легким движением руки с помощью типа union (а если быть точнее — структуры внитри объединения) получаем доступ по нужному смещению буфера
    while (ftell(File) < TagSize + 10) { // смотрим на текущее положение указателя и спрашиваем, больше ли оно, чем реверснутый размер тэга
        FrameTag Frame; // обращаемся ко второму объединению
        fread(Frame.Buffer, sizeof(char), 10, File); // считываем из File 10 объектов длины char и запихиываем в буфер фрейма
        if (Frame.FrameData.Name[0] == 0) { // если имя файла — не имя файла (то есть там ничего нет), то можно дальше не читать, так как там ничего не будет
            break;
        }
        printf("%s: ", Frame.FrameData.Name); // выводим имя файла
        unsigned int FrameSize = Reverse(Frame.FrameData.Size); // опять реверсим
        unsigned char* FrameContent = malloc(sizeof(char) *FrameSize); // создаем динамическую строку для фрейм контента
        fread(FrameContent, sizeof(char), FrameSize, File); // считываем FrameSize элеметов длины char в FrameContent из File
        for (int i = 0; i < FrameSize; ++i) { // проходимся по каждому символу...
            printf("%c", FrameContent[i]); //... и печатаем посимвольно каждый символ из фрейма
        }
        printf("\n"); // переход на следующую строку
        free(FrameContent); // освобождаем позаимствованное место
    }
    fclose(File); // закрываем файл
}
 
void Get(char *FileName, char FrameName[4]) {
    FILE* File = fopen(FileName, "rb"); // открываем НЕТЕКСТОВЫЙ (для текстового используется просто "r") файл на чтение (да, я скопировал это с предыдущего)
    TagTag Tag; // вызываем юнион TagTag
    fread(Tag.Buffer + 2, sizeof(char), 10, File); // считываем из File 10 объектов длины char и запихиываем в буфер тэга, начиная со 2 байта
    unsigned int TagSize = Reverse(Tag.TagData.Size); // реверсим
    while (ftell(File) < TagSize + 10) { // смотрим на положение указателя и работаем
        FrameTag Frame; // открываем union FrameTag
        fread(Frame.Buffer, sizeof(char), 10, File); // читаем в буфер фрейма посивольно
        unsigned int FrameSize = Reverse(Frame.FrameData.Size); // реверсим размер
        if (strcmp((char*)Frame.FrameData.Name, FrameName) == 0) { // сравниваем название считанного и запрошенного фрейма, если не совпадают, то идем, пока не найдем, либо не обнаружим, что такого фрейма нет
            printf("%s: ", Frame.FrameData.Name); // выводим название фрейма
            unsigned char *FrameContent = malloc(sizeof(char) *FrameSize); // создаем динамическую строку
            fread(FrameContent, sizeof(char), FrameSize, File); // считываем FrameSize элеметов длины char в FrameContent из File
            for (int i = 0; i < FrameSize; ++i) {
                printf("%c", FrameContent[i]); // посимвольно печатаем значение фрейма
            }
            printf("\n"); // переход на следующую строку
            free(FrameContent); // освобождаем место
            fclose(File); // закрываем файл
            return; // завершаем, если найдено
        }
        fseek(File, FrameSize, 1); // возврашает указатель на текущее положение курсора, со смещением на FrameSize
    }
    fclose(File); // закрываем файл
}
 
void Set(char *FileName, char FrameName[4], char *FrameValue) {
    FILE* File = fopen(FileName, "rb"); // открываем НЕТЕКСТОВЫЙ (для текстового используется просто "r") файл на чтение (скопировал уже во 2 раз)
    TagTag Tag; // ТэгТэг Тэг
    fread(Tag.Buffer + 2, sizeof(char), 10, File); // // считываем из File 10 объектов длины char и запихиываем в буфер тэга, начиная со 2 байта (да, это пояснение я тоже скопировал)
    unsigned int TagSize = Reverse(Tag.TagData.Size), OldFramePosition = 0, OldFrameSize = 0; // создаем много новых переменных, название которых говорит само за себя
    while (ftell(File) < TagSize + 10) { // смотрим на положение курсора и работаем
        FrameTag Frame; // ФреймТэг Фрейм
        fread(Frame.Buffer, sizeof(char), 10, File); // читаем в фреймовский буфер 10 элементов размера char
        unsigned int FrameSize = Reverse(Frame.FrameData.Size); // реверсим
        if (strcmp((char*)Frame.FrameData.Name, FrameName) == 0) { // сравниваем название считанного и запрошенного фрейма, если не совпадают, то идем, пока не найдем, либо не обнаружим, что такого фрейма нет
            OldFramePosition = (unsigned int)ftell(File) - 10; //показвыаем, что текущее указание на фрейм — текущее положение курсора - 10
            OldFrameSize = FrameSize; // а размер фрейма копируем как страный размер
            break; // сделал дело — гуляй смело
        }
        fseek(File, FrameSize, 1); // возвращаем текущее положение курсора, сдивнутое на фреймсайз
    }
    unsigned int ValueSize = (unsigned int)strlen(FrameValue), NewTagSize = TagSize - OldFrameSize + ValueSize + 10 * (OldFramePosition != 0); // Ничего интересного, просто новые переменные
    if (OldFramePosition == 0) { // если позоция старого фрейма равна нулю
        OldFramePosition = (unsigned int)ftell(File); // тогда такого фрейма нет и мы просто смещаемся
    }
    if (ValueSize == 0) { // если новое значение равно нулю
        NewTagSize -= 10; // то этот тэг следует уничтожить
    }
    FILE* FileCopy = fopen("temp.mp3", "wb"); // создаем temp.mp3, КОТОРЫЙ ОТКРЫВАЕМ НА ЗАПИСЬ НЕТЕКСТОВОГО ФАЙЛА
    fseek(File, 0, 0); // ставим курсор в начало исходного файла
    fseek(FileCopy, 0, 0); // ставим курсор в начало созданного файла
    Copy(File, FileCopy); // копируем
    fclose(File); // закрываем одно
    fclose(FileCopy); // закрываем другое
    FileCopy = fopen("temp.mp3", "rb"); // открываем новоиспеченный файл на чтение
    File = fopen(FileName, "wb"); // открываем исходный файл на запись
    Tag.TagData.Size = Reverse(NewTagSize); // реверсим
    fwrite(Tag.Buffer + 2, sizeof(char), 10, File); // записываем поэлементно 10 символов в буфер, начиная со 2
    fseek(FileCopy, 10, 0); // переходим на 10 символов вперед в новом файле
    for (int i = 0; i < OldFramePosition - 10; ++i) { // посимвольно читаем
        int Char = getc(FileCopy); // присваиваем символ
        putc(Char, File); // суем символ
    }
    if (ValueSize > 0) { // если новое значение больше нуля
        FrameTag Frame; // фрейм
        for (int i = 0; i < 4; ++i) // 4 байтика
            Frame.FrameData.Name[i] = FrameName[i]; //записывем имя
        Frame.FrameData.Size = Reverse(ValueSize); // реверсим
        Frame.FrameData.Flags = 0; // флаг на 0
        fwrite(Frame.Buffer, sizeof(char), 10, File); // записываем 10 байтиков в фреймовский буфер
    }
    fwrite(FrameValue, sizeof(char), ValueSize, File); // записываем новое значение фрейма
    fseek(FileCopy, OldFramePosition + 10 + OldFrameSize, 0); // ищем старый фрейм
    for (int i = (int)ftell(File); i < NewTagSize; ++i) { // проходимся по значниям тэга
        int Char = getc(FileCopy); // берем символ
        putc(Char, File); // вставляем символ
    }
    printf("Новое значение для поля %s: %s\n", FrameName, FrameValue); // вывод
    Copy(FileCopy, File); // копируем все назад
    fclose(File); // закрывем одно
    fclose(FileCopy); // и другое
    remove("temp.mp3"); // и удаляем другое
}
 
int main(int argc, char *argv[]) {
    char *FileName = NULL, *FrameName = NULL, *Value = NULL, ShowFlag = 0, SetFlag = 0, GetFlag = 0; // много строк и символов
    for (int i = 1; i < argc; i++) { // проходимся по введенным в консоли значениям
        if (strcmp(argv[i], "--show") == 0) { // если видим, что надо показать...
            ShowFlag = 1; //... то ставим флаг показывания в положение 1
            continue; // дальше
        }
        if (argv[i][2] == 'f') { // если встречаем команду на f (спойлер: --filepath)
            FileName = strpbrk(argv[i], "=") + 1; // то записываем имя файла
        }
        if (argv[i][2] == 'g') { // если встречсем команду на g (спойлер: --get)
            GetFlag = 1; // то ставим флаг, что надо вывести определнный фрейм
            FrameName = strpbrk(argv[i], "=") + 1; // записываем название этого фрейма
            continue; // дальше
        }
        if (argv[i][2] == 's') { // если встречаем команду на s, но не --show (спойлер: --set)
            SetFlag = 1; // флаг установки устаналиваем в положение 1
            FrameName = strpbrk(argv[i], "=") + 1; // название фрейма
            continue;
        }
        if (argv[i][2] == 'v') { // если встречаем команду на v (спойлер: --value)
            Value = strpbrk(argv[i], "=") + 1; // то записываем это значение
            continue; // дальше
        }
    }
    if (ShowFlag) {
        Show(FileName); // если флаг показа выставлен, то показать
    }
    if (GetFlag) {
        Get(FileName, FrameName); // если флаг выведения одного фрейма стоит, то вывести фрейм
    }
    if (SetFlag) {
        Set(FileName, FrameName, Value); // если просят что-то записать — запиши
    }
}
