#ifndef OPTIONS_H
#define OPTIONS_H

/*
 * DEFINES:
*/

#define _MAX_SYSTEM_FILES 10000
#define _MAX_SIGNATURE_SIZE 16384
#define _NANO_MULTIPLIER 1000000000
#define _BEGET_U_MAXCHARS 6
#define _MAX_ARGUMENTS 4 // Количество аргументов включая сокращённые.

/*
 * OPTION LIST:
*/

enum arguments {help, passive, log, extlog};

char *arg_longarg_list[_MAX_ARGUMENTS] =
{
"--help",       // 0
"--passive",    // 1
"--log",        // 2
"--extlog"      // 3
};

char *arg_shortarg_list[_MAX_ARGUMENTS] =
{
"-h",
"-p",
"-l",
"-L"
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
static const unsigned int opt_log = 2;
static const unsigned int opt_extlog = 4;
static const unsigned int opt_monothr = 8;

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
Неверный аргумент %s!\n\
Аргумент с таким именем недоступен.\n\
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
bool arg_is_long = false;
bool arg_is_valid = false;

#endif // OPTIONS_H
