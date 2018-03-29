//
//  Environnement.cpp
//  tabou
//
//  Created by Valérian Acier on 27/03/2018.
//  Copyright © 2018 Valérian Acier. All rights reserved.
//

#include "evaluateur.hpp"
#include <cmath>

using namespace std;

Evaluateur::Evaluateur(vector<double> &constants)
{
    this->constants = constants;
    initDayToMonth();
}

double Evaluateur::evaluate(std::vector<Variable *> &variables)
{
    double totalDelta = 0;

    return totalDelta;
}

double Evaluateur::evaluate(vector<Variable> &variables)
{
    double totalCost = 0;
    map<int, double> livraison;
    this->state = this->constants;
    this->state.push_back(state[STOCK]);

    for (int i = 1; i < 262; i++)
    {
        this->state[STOCK] = state[STOCK] - calculOrder(i) + livraison[i];
        this->state[VIRTUAL_STOCK] = state[VIRTUAL_STOCK] - calculOrder(i);
        if (this->state[STOCK] < 0)
        {
            // Cas Rupture
            totalCost -= state[STOCK] * constants[PURCHASE_PRICE] * constants[OUT_STOCK_PERCENT];
        }
        else
        {
            if (i % 5 == 0)
            {
                // Cas stockage Vendredi
                totalCost += (state[STOCK] * constants[PURCHASE_PRICE] * constants[OWNERSHIP_RATE] * 3) / 365;
            }
            else
            {
                // Cas stockage Semaine
                totalCost += (state[STOCK] * constants[PURCHASE_PRICE] * constants[OWNERSHIP_RATE]) / 365;
            }
        }
        double delivery = evaluatePointControle(variables, state, i);
        livraison[i + constants[DELAY_LIVRAISON]] = delivery;
        state[VIRTUAL_STOCK] += delivery;
        if (delivery > 0)
            totalCost += constants[ORDER_COST];

        cout << "Stock " << state[STOCK] << endl;
    }

    return totalCost;
}

double Evaluateur::evaluatePointControle(std::vector<Variable> &variables, std::vector<double> state, int day)
{
    if (state[VIRTUAL_STOCK] >= variables[2].value)
        return 0;
    return variables[1].value;
}

double Evaluateur::calculOrder(int day)
{
    return (this->constants[INITIAL_DEMANDE] + (day * this->constants[INCREASE])) * (dayToMonth[day] == constants[MONTH_SAISONALITY] ? 1 + constants[PERCENT_OF_SAISONALITY] : 1);
}

void Evaluateur::initDayToMonth() {
    for (int i = 0; i < 24; i++)
    {
        dayToMonth[i] = 1;
    }
    for (int i = 24; i < 44; i++)
    {
        dayToMonth[i] = 2;
    }
    for (int i = 44; i < 66; i++)
    {
        dayToMonth[i] = 3;
    }
    for (int i = 66; i < 87; i++)
    {
        dayToMonth[i] = 4;
    }
    for (int i = 87; i < 110; i++)
    {
        dayToMonth[i] = 5;
    }
    for (int i = 110; i < 131; i++)
    {
        dayToMonth[i] = 6;
    }
    for (int i = 131; i < 153; i++)
    {
        dayToMonth[i] = 7;
    }
    for (int i = 153; i < 176; i++)
    {
        dayToMonth[i] = 8;
    }
    for (int i = 176; i < 196; i++)
    {
        dayToMonth[i] = 9;
    }
    for (int i = 196; i < 219; i++)
    {
        dayToMonth[i] = 10;
    }
    for (int i = 219; i < 241; i++)
    {
        dayToMonth[i] = 11;
    }
    for (int i = 241; i < 262; i++)
    {
        dayToMonth[i] = 12;
    }
}