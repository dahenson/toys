#include<stdio.h>

#include "energy_math.h"
#include "fixture.h"

Fixture
fixture_new(void)
{
    struct Fixture f = {
        0, /* bulb_count */
        0, /* bulb_cost */
        0, /* bulb_life */
        0, /* bulb_watts */
        0, /* hrs */
    };

    return f;
}

double
fixture_kwh(Fixture *f)
{
    double kwh = f->bulb_count * kilowatt_hours(f->bulb_watts, f->hrs);
    return kwh;
}

double
fixture_bulb_life_years (Fixture *f)
{
    return f->bulb_life / f->hrs / 365;
}

void
fixture_pretty_print_stats(Fixture *f, double energy_price)
{
    double kwh = fixture_kwh(f);
    double cpd = cost_per_day(kwh, energy_price);

    printf("\n");
    printf("      %.0d bulbs @ %-5.2f watts\n", f->bulb_count, f->bulb_watts);
    printf("        %-4.1f hours / day\n", f->hrs);
    printf("  +--------+---------+--------+\n");
    printf("  | $/week | $/month | $/year |\n");
    printf("  +--------+---------+--------+\n");
    printf("  |$%-6.2f |$%-6.2f  |$%-6.2f |\n", cpd * 7, cpd * 30, cpd * 365);
    printf("  +--------+---------+--------+\n");
    printf("  |Expected Life: %-6.2f years|\n", fixture_bulb_life_years(f));
    printf("  +---------------------------+\n\n");
}
