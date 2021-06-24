def getData(x, y, z):
    x /= 8.0
    y /= 8.0
    z /= 8.0
    a = [
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,

        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,

        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,

        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,

        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,

        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
    ]
    return a;

vertexData = []
for x in range(0, 8):
    for y in range(0, 8):
        for z in range(0, 8):
            vertexData += getData(x, y, z)

file = open("index.txt", "w")
file.write(str(vertexData))
file.close()
