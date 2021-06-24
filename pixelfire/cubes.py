def getData(x, y, z):
    st = 0.5
    su = (st * 2.0) / 8.0
    ox = (x * su) - (st / 2.0)
    oy = (y * su) - (st / 2.0)
    oz = (z * su) - (st / 2.0)
    a = [
        -1.0 * su + ox, -1.0 * su + oy, -1.0 * su + oz,
        -1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,
         1.0 * su + ox, -1.0 * su + oy, -1.0 * su + oz,
        -1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,
         1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,
         1.0 * su + ox, -1.0 * su + oy, -1.0 * su + oz,

        -1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,
         1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,
        -1.0 * su + ox,  1.0 * su + oy,  1.0 * su + oz,
        -1.0 * su + ox,  1.0 * su + oy,  1.0 * su + oz,
         1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,
         1.0 * su + ox,  1.0 * su + oy,  1.0 * su + oz,

        -1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,
        -1.0 * su + ox,  1.0 * su + oy,  1.0 * su + oz,
         1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,
        -1.0 * su + ox,  1.0 * su + oy,  1.0 * su + oz,
         1.0 * su + ox,  1.0 * su + oy,  1.0 * su + oz,
         1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,

        -1.0 * su + ox, -1.0 * su + oy, -1.0 * su + oz,
         1.0 * su + ox, -1.0 * su + oy, -1.0 * su + oz,
        -1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,
        -1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,
         1.0 * su + ox, -1.0 * su + oy, -1.0 * su + oz,
         1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,

        -1.0 * su + ox, -1.0 * su + oy, -1.0 * su + oz,
        -1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,
        -1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,
        -1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,
        -1.0 * su + ox,  1.0 * su + oy,  1.0 * su + oz,
        -1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,

         1.0 * su + ox, -1.0 * su + oy, -1.0 * su + oz,
         1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,
         1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,
         1.0 * su + ox, -1.0 * su + oy,  1.0 * su + oz,
         1.0 * su + ox,  1.0 * su + oy, -1.0 * su + oz,
         1.0 * su + ox,  1.0 * su + oy,  1.0 * su + oz,
    ]
    return a;

vertexData = []
for x in range(0, 8):
    for y in range(0, 8):
        for z in range(0, 8):
            vertexData += getData(x, y, z)

file = open("cubes.txt", "w")
file.write(str(vertexData))
file.close()
