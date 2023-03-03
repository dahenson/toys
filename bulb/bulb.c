#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "energy_math.h"
#include "fixture.h"

static const char *PROG_NAME = "bulb";
static const char *VERSION = "0.0.1";

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

    struct Fixture f = fixture_new();

    double price = 0;

    char *badchar;

    /* Running the program without arguments won't do anything. */
    if (argc == 1) {
        print_help_message();
        exit(EXIT_SUCCESS);
    }

    while ((opt = getopt(argc, argv, ":ha:b:l:p:va:w:")) != -1) {
        switch (opt){
            case 'a':
                f.hrs = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    exit_with_error_message("error: hours should be a number\n");
                }

                if (f.hrs < 0 || f.hrs > 24) {
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
                f.bulb_life = strtod(optarg, &badchar);

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
                f.bulb_watts = strtod(optarg, &badchar);

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

    fixture_pretty_print_stats(&f, price);

    exit(EXIT_SUCCESS);
}
