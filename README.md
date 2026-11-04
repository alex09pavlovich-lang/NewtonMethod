
# Newton Method - Cubic Equation Solver

## Project Description

This project implements the Newton numerical method
for finding real roots of a cubic equation.

The program solves:

ax^3 + bx^2 + cx + d = 0

## Method

The Newton method uses the following formula:

x(n+1) = x(n) - f(x(n)) / f'(x(n))

The derivative is:

f'(x) = 3ax^2 + 2bx + c

## Features

- Input of cubic equation coefficients.
- Multiple initial approximations.
- Numerical search for real roots.
- Calculation of residuals.
- Counting iterations.
- Removing duplicate roots.

## Test Example

Input:

1 -6 11 -6

Expected roots:

1, 2, 3

## Technologies

- C++
- Visual Studio 2026
- CMake
- Git
