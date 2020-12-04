#include "branch.h"

branch::branch(sequence seq)
 : seq(seq) {

}

sequence branch::get_sequence() {
    return this->seq;
}

branch::~branch() {

}