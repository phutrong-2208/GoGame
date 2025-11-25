#ifndef ROUNDED_RECTANGLE_HPP
#define ROUNDED_RECTANGLE_HPP

#include <math.h>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <SFML/Graphics.hpp>

const double pi = 3.141592653589793L;

void roundedRectangle(sf :: RenderWindow &window, sf :: Vector2<double> A, sf :: Vector2<double> B, sf :: Color col, double radius = 10.0L);

void customPanelRender(sf :: RenderWindow &window, sf :: Vector2<double> A, sf :: Vector2<double> B, sf :: Color col);
void customPanelRender(sf :: RenderWindow &window, sf :: RectangleShape shape);

#endif