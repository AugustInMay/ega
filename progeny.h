//
// Created by augustinmay on 08.11.19.
//

#ifndef EGA10_PROGENY_H
#define EGA10_PROGENY_H

#include <string>

class progeny {
    int generation;
    int size;
    int *gen;
    double tot_dist;
public:
    progeny(void);
    progeny(int g, int s, int *gen, bool first, bool rnd, bool bef, int entry, double **R, bool show_proc);
    progeny(int g, int s, int *gen, double **R):progeny(g, s, gen, false, false, false, 0, R){};
    progeny(int g, int s, int *gen, bool first, double **R):progeny(g, s, gen, true, false, false, 0, R){};
    progeny(int g, int s, int *gen, bool first, bool rnd, bool bef, int entry, double **R):progeny(g, s, gen, first, rnd, bef, entry, R, false){};
    progeny(const progeny &pr);
    ~progeny(void);
    bool operator==(const progeny &r);
    bool operator==(const int *r);
    bool operator>=(const progeny &r);
    bool operator>=(const int &r);
    bool operator!=(const progeny &r);
    int& operator[] (int x);

    void dist_cnt(double **R);
    void ran_gen();
    void closest_n(double **R, bool pre);
    void closest_c(double **R, bool pre);
    void show_gen();
    std::string show_str_gen();
    int get_gener();
    double get_dist();
};

#endif //EGA10_PROGENY_H
