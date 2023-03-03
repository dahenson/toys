#ifndef FIXTURE_H_
#define FIXTURE_H_

struct Fixture {
    int bulb_count;
    double bulb_cost;
    double bulb_life;
    double bulb_watts;
    double hrs;
};

struct Fixture fixture_new(void);
double fixture_bulb_life_years(struct Fixture *f);
double fixture_kwh(struct Fixture *f);
void fixture_pretty_print_stats(struct Fixture *f, double energy_price);

#endif /* FIXTURE_H_ */

