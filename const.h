#ifndef OPTIONS_H
#define OPTIONS_H

/*
 * DEFINES:
*/

#define _MAX_SYSTEM_FILES 10000
#define _MAX_SIGNATURE_SIZE 16384
#define _NANO_MULTIPLIER 1000000000
#define _BEGET_U_MAXCHARS 6
#define _MAX_ARGUMENTS 8 // Количество аргументов включая сокращённые.

/*
 * OPTION LIST:
*/

char *arg_list[8] =
{
"h", "help",
"p", "passive",
"l", "log",
"L", "extlog"
};

static char *mess_arg_list =
"\n\
-p --passive        Пассивный режим. В данном режиме происходит только проверка, без удаления.\n\
-m --mono           Режим монозадачности. В данном режиме не происходит многопоточной обработки.\n\
-l --log            Режим логирования. В данном режиме логируется список обработанных файлов.\n\
-L --extlog         Режим расширенного логирования. В данном режиме логируются все действия программы.\n\
\n";

/*
 * OPTIONS:
*/

static unsigned int opt_bites = 0;
static const unsigned int opt_passive = 1;
static const unsigned int opt_scanlog = 2;
static const unsigned int opt_monothr = 4;

/*
 * SYSTEM MESSAGES INCLUDING ERRORS:
*/

static char *mess_usage =
"\
Использование: \n\
litedet [ИМЯ ПОЛЬЗОВАТЕЛЯ]... [КЛЮЧ]...\n\
Например: \n\
litedet [beelin7h] -p\n";

static char *mess_arg_wrong =
"\
Аргументы представлены в неверном формате!\n\
Аргумента %s нет\n\
Внимание: Все аргументы регистрозависимы.\n";

static char *mess_arg_toomany =
"\
Слишком много аргументов!\n";

static char *mess_arg_maybe =
"\
Ошибка синтаксиса, аргументы представлены в неверном формате!\n\
Возможно вы имели ввиду --%s и пропустили символы '-'?\n\
Внимание: Все аргументы регистрозависимы.\n";

/*
 * OTHER:
*/

static unsigned int mrk = 0;
static char *sec_arg;

#endif // OPTIONS_H
