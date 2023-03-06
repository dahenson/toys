#ifndef FIXTURE_H_
#define FIXTURE_H_

typedef struct Fixture {
    int bulb_count;
    double bulb_cost;
    double bulb_life;
    double bulb_watts;
    double hrs;
} Fixture;

Fixture fixture_new(void);
double fixture_bulb_life_years(Fixture *f);
double fixture_kwh(Fixture *f);
void fixture_pretty_print_stats(Fixture *f, double energy_price);

#endif /* FIXTURE_H_ */

