/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHVECTOR_SWITCHVECTOR_H_
#define SRC_SWITCHVECTOR_SWITCHVECTOR_H_

#define N_KEYS 4

namespace switch_vector {

typedef enum switch_state_t {
    PRESSED, RELEASED,
} key_state_t;

/*
SwitchVector is used to represent switchboard states.

It might contain some modifier logic later on. Seems
like the best place for it, since the translation
service is going to need some state information
on the modifiers, and this one is going to get passed
around I think. Idk.

Right now there's no real reason to encapsulate this
in a class, but I have a feeling we're going to need
it in the future. We might just decide to start using
bitwise storage instead of an entire int for each switch,
and I don't want other parts of the code to have to
deal with implementation here.
*/
class SwitchVector {
 public:
    SwitchVector();
    void set(int n_switch, switch_state_t state);
    int get(int n_switch);
    ~SwitchVector();
 private:
    key_state_t switchVector[N_KEYS];
};

} // namespace switch_vector


#endif // SRC_SWITCHVECTOR_SWITCHVECTOR_H_
