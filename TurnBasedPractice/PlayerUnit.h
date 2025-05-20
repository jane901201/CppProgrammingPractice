#pragma once
#include "Unit.h"
#include <string>

class PlayerUnit : public Unit {
public:
    PlayerUnit() : mHP(100), mRage(0) {}

    int GetHP() const override { return mHP; }
    void SetHP(int hp) override { mHP = hp; }

    int GetRage() const override { return mRage; }
    void SetRage(int rage) override { mRage = rage; }

    const char* GetName() const override { return "Farmer"; }

    void TakeDamage(int amount) override {
        mHP -= amount;
        if (mHP < 0) mHP = 0;
    }

    void AddRage(int amount) override {
        mRage += amount;
        if (mRage > 10) mRage = 10;
    }

private:
    int mHP;
    int mRage;
};