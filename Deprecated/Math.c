#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#define PI 3.141
#define _Abs(value) ( (value) >= 0 ? (value) : -(value) )
#define _Round(value) ( (value) % 1 > 0.5 ? ((int) (value) + 0.5) : ((int) (value)) )
#define _Sign(value) ( (value) >= 0 ? 1 : (-1) )
#define _Cube(value) ( (value) * (value) * (value) )

#define _InchesToTicks(inches, diam) ( ((inches) / (PI * (diam))) * 360 )
#define _TicksToInches(ticks, diam) ( ((diam) * PI) * ((ticks) / 360) )

#endif