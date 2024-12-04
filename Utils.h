#pragma once
#include "Chain_Base.h"
#include "Chain.h"

/// <summary>
/// A generic utils namespace
/// </summary>
namespace utils {
    static Chain_Base* constructChain(char type) {
        Chain_Base* cb1{};
        if (type == 'R') {
            cb1 = new Chain<Red>();
        }
        else if (type == 'B') {
            cb1 = new Chain<Blue>();
        }
        else if (type == 'C') {
            cb1 = new Chain<Chili>();
        }
        else if (type == 'S') {
            cb1 = new Chain<Stink>();
        }
        else if (type == 'G') {
            cb1 = new Chain<Green>();
        }
        else if (type == 's') {
            cb1 = new Chain<soy>();
        }
        else if (type == 'b') {
            cb1 = new Chain<black>();
        }
        else if (type == 'g') {
            cb1 = new Chain<garden>();
        }
        return cb1;
    }
}