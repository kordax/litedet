#ifndef OPTIONS_H
#define OPTIONS_H

/*
 * OPTIONS:
*/

static unsigned int opt_bites = 0;
static const unsigned int opt_passive = 1;
static const unsigned int opt_scanlog = 2;
static const unsigned int opt_monothr = 4;

/*
 * DEFINES:
*/

#define _MAX_SYSTEM_FILES 10000
#define _MAX_SIGNATURE_SIZE 16384
#define _NANO_MULTIPLIER 1000000000
#define _BEGET_U_MAXCHARS 6

/*
 * SYSTEM MESSAGES INCLUDING ERRORS:
*/

static char *mess_usage =
"Использование: \n\
litedet [ИМЯ ПОЛЬЗОВАТЕЛЯ]... [КЛЮЧ]...\n\
Например: \n\
litedet [beelin7h] -p\n";

static char *mess_arg_wrong =
"Аргументы представлены в неверном формате!\n\
Все аргументы регистрозависимы!\n";

static char *mess_arg_toomany =
"Слишком много аргументов!\n";

/*
 * OTHER:
*/

static unsigned int mrk = 0;

#endif // OPTIONS_H
