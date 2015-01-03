#ifndef OPTIONS_H
#define OPTIONS_H

/*
 * DEFINES:
*/

#define _LITE_MAX_FILES 10000
#define _LITE_MAX_SIGNSIZE 16384
#define _LITE_TIMERNANOMTPL 1000000000
#define _LITE_MAX_UNAMESIZE 6
#define _LITE_OPTIONS 5 // Количество аргументов включая сокращённые.

/*
 * OPTION LIST:
*/

enum arguments {help, active, log, extlog, debug};

char *arg_longarg_list[_LITE_OPTIONS] =
{
"--help",       // 0
"--active",    // 1
"--log",        // 2
"--extlog",     // 3
"--debug"       // 4
};

char *arg_shortarg_list[_LITE_OPTIONS] =
{
"-h",
"-a",
"-l",
"-L",
"-d"
};

static char *mess_arg_list =
"\n\
Аргументы, обязательные для длинных ключей, обязательны и для коротких.\n\
    -a --active         Активный режим. В данном режиме происходит проверка с удалением.\n\
    -m --mono           Режим монозадачности. В данном режиме не происходит многопоточной обработки.\n\
    -l --log            Режим логирования. В данном режиме логируется список обработанных файлов.\n\
    -L --extlog         Режим расширенного логирования. В данном режиме логируются все действия программы.\n\
    -d --debug          Режим отладки. В данном режиме выводится вся дополнительная информация.\n";

/*
 * OPTION BITES:
*/

static unsigned int opt_bites = 0;
static const unsigned int opt_active = 1;
static const unsigned int opt_log = 2;
static const unsigned int opt_extlog = 4;
static const unsigned int opt_monothr = 8;
static const unsigned int opt_debug = 16;

/*
 * SYSTEM MESSAGES INCLUDING ERRORS:
*/

static char *mess_usage =
"\
Использование:  ./litedet [ИМЯ ПОЛЬЗОВАТЕЛЯ]... [КЛЮЧ]...\n\
Например:       ./litedet [beelin7h] -p\n\
По-умолачнию, програма сверяет файлы с сигнатурами и удаляет найденный вредоносный код.\n";

static char *mess_arg_wrong =
"\
Неверный ключ %s!\n\
Используйте --help для получения списка доступных ключей\n\
Внимание: Все аргументы регистрозависимы.\n";

static char *mess_arg_toomany =
"\
Слишком много аргументов!\n";

static char *mess_arg_maybe =
"\
Ошибка синтаксиса, аргументы представлены в неверном формате!\n\
Возможно вы имели ввиду --%s и пропустили символы '-'?\n\
Внимание: Все аргументы регистрозависимы.\n";

static char *mess_found_multiple =
"\
Найдено %d вредоносных файлов.\n";

static char *mess_found_onlyone =
"\
Найден %d вредоносный файл.\n";

/*
 * OTHER:
*/

static unsigned int con_mark         =   0;
static unsigned int con_equal   =   0;
bool arg_is_long                =   false;
bool arg_is_valid               =   false;
static char *sec_arg;

#endif // OPTIONS_H
