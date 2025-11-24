import math

def get_dist(big_x, big_y, x, y, s, r):
    small_x = (s / 100.0) * big_x
    small_y = (s / 100.0) * big_y

    temp_r = math.sqrt(small_x * small_x + small_y * small_y)
    theta = math.atan2(big_y, big_x)

    theta += r * 2 * math.pi / 360.0

    small_x = math.cos(theta) * temp_r + x
    small_y = math.sin(theta) * temp_r + y

    dist = math.sqrt((big_x - small_x) ** 2 + (big_y - small_y) ** 2)
    return dist

def main():
    import sys
    
    for line in sys.stdin:
        data = line.split()
        if not data:
            continue
            
        w, h, x, y, s, r = map(int, data)
        
        if w == 0 and h == 0 and x == 0 and y == 0 and s == 0 and r == 0:
            break

        minx, maxx = 0.0, float(w)
        miny, maxy = 0.0, float(h)

        while maxx - minx > 0.0000001:
            scalex = maxx - minx
            scaley = maxy - miny

            lx = scalex * 0.25 + minx
            hx = scalex * 0.75 + minx
            ly = scaley * 0.25 + miny
            hy = scaley * 0.75 + miny

            d1 = get_dist(lx, ly, x, y, s, r)
            d2 = get_dist(hx, ly, x, y, s, r)
            d3 = get_dist(lx, hy, x, y, s, r)
            d4 = get_dist(hx, hy, x, y, s, r)

            avgx = (minx + maxx) / 2
            avgy = (miny + maxy) / 2

            if d1 < d2 and d1 < d3 and d1 < d4:
                maxx = avgx
                maxy = avgy
            elif d2 < d1 and d2 < d3 and d2 < d4:
                minx = avgx
                maxy = avgy
            elif d3 < d2 and d3 < d1 and d3 < d4:
                maxx = avgx
                miny = avgy
            elif d4 < d2 and d4 < d3 and d4 < d1:
                minx = avgx
                miny = avgy

        print(f"{minx:.2f} {miny:.2f}")

if __name__ == "__main__":
    main()