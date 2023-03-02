#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "energy_math.h"

static const char *PROG_NAME = "bulb";
static const char *VERSION = "0.0.1";

struct bulb {
    double cost;
    double life;
    double watts;
};

struct fixture {
    int bulb_count;
    double hours;
    double kwh;
};

static void
exit_with_error_message(const char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

static void
print_help_message(void)
{
    printf("%s - calculate lightbulb fixture cost and lifespan.\n", PROG_NAME);
    printf("\nUsage: %s [options]\n", PROG_NAME);
    printf("\t-h          print the help message\n");
    printf("\t-a hours    the average hours the bulb is on\n");
    printf("\t-b bulbs    the number of bulbs in the fixture (default: 1)\n");
    printf("\t-l life     expected lifespan in hours (default: 11000)\n");
    printf("\t-p price    the price per kWh\n");
    printf("\t-v version  print the version\n");
    printf("\t-w watts    the wattage of the bulb\n");
    printf("\nExample:\n");
    printf("\n\t%s -a 6 -p 0.10 -w 11\n\n", PROG_NAME);
}

int
main(int argc, char *const argv[])
{
    int opt;

    struct bulb b = {
        .cost = 0,
        .life = 11000,
        .watts = 0
    };

    struct fixture f = {
        .bulb_count = 1,
        .hours = 0
    };

    double
        kwh = 0,
        cpd = 0,
        price = 0;

    char *badchar;

    /* Running the program without arguments won't do anything. */
    if (argc == 1) {
        print_help_message();
        exit(EXIT_SUCCESS);
    }

    while ((opt = getopt(argc, argv, ":ha:b:l:p:va:w:")) != -1) {
        switch (opt){
            case 'a':
                f.hours = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    exit_with_error_message("error: hours should be a number\n");
                }

                if (f.hours < 0 || f.hours > 24) {
                    exit_with_error_message("error: hours must be between 0 and 24\n");
                }

                break;
            case 'b':
                f.bulb_count = strtol(optarg, &badchar, 10);

                if (*badchar != '\0') {
                    exit_with_error_message("error: bulbs should be a number\n");
                }
                break;
            case 'l':
                b.life = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    exit_with_error_message("error: life should be a number\n");
                }
                break;
            case 'p':
                price = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    exit_with_error_message("error: price should be a number\n");
                }
                break;
            case 'v':
                printf("\n%s - version %s\n", PROG_NAME, VERSION);
                exit(EXIT_SUCCESS);
                break;
            case 'w':
                b.watts = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    exit_with_error_message("error: watts should be a number\n");
                }
                break;
            case 'h':
                print_help_message();
                exit(EXIT_SUCCESS);
                break;
            default:
                print_help_message();
                exit(EXIT_SUCCESS);
                break;
        }
    }

    kwh = kilowatt_hours(b.watts, f.hours);
    cpd = cost_per_day(kwh, price);

    printf("\n");
    printf("      %.0d bulbs @ %-5.2f watts\n", f.bulb_count, b.watts);
    printf("        %-4.1f hours / day\n", f.hours);
    printf("  +--------+---------+--------+\n");
    printf("  | $/week | $/month | $/year |\n");
    printf("  +--------+---------+--------+\n");
    printf("  |$%-6.2f |$%-6.2f  |$%-6.2f |\n", cost_per_week(cpd), cost_per_month(cpd), cost_per_year(cpd));
    printf("  +--------+---------+--------+\n");
    printf("  |Expected Life: %-6.2f years|\n", life_in_years(b.life, f.hours));
    printf("  +---------------------------+\n\n");

    exit(EXIT_SUCCESS);
}
