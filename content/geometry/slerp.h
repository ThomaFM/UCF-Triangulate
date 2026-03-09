/**
 * Author: Brian Barak
 * Date: 2026-03-08
 * Description: Interpolates between two points on a sphere centered at the origin
 * Status: Tested by LLM lmao. Very unlikely to have any issues unless the vectors are antipodal.
 */
#pragma once

const ld EPS = 1e-9;
template<class T> T mix(T a, T b, ld p) {
  return a + (b - a) * p; }
P slerp(P a, P b, ld p) {
  if (a.dist() < EPS || b.dist() < EPS)
    return mix(a, b, p);
  ld len = mix(a.dist(), b.dist(), p);
  a = a / a.dist(); b = b / b.dist();
  ld dot = a.dot(b);
  if (dot >= 1 - EPS) { // vectors going in the same direction
    return mix(a, b, p) * len; }
  else if (dot <= -1 + EPS) { // vectors going in opposite directions
    P arb = P(1, 0); // arbitrary point to go through
    if (abs(arb.dot(b)) >= 1 - EPS) arb = P(0, 1);
    ld o = acos(a.dot(arb)) / PI;
    if (p < o) return slerp(a, arb, p / o) * len;
    return slerp(arb, b, (p - o) / (1 - o)) * len; }
  ld o = acos(dot), so = sin(o);
  return (a * (sin((1 - p) * o) / so)
    + b * (sin(p * o) / so)) * len; }