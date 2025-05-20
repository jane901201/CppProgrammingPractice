#pragma once

class Unit {
public:
    virtual ~Unit() {}

    virtual int GetHP() const = 0;
    virtual void SetHP(int hp) = 0;

    virtual int GetRage() const = 0;
    virtual void SetRage(int rage) = 0;

    virtual const char* GetName() const = 0;

    virtual void TakeDamage(int amount) = 0;
    virtual void AddRage(int amount) = 0;
};
