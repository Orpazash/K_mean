from sys import argv


def compute_distance(dot1, dot2):
    return None


def add_to_cluster(dot, old_centroids):
    return None


def check_delta_cenroids(old_centroids, new_centroids):
    return None


def compute_centroid(cluster_array):
    return sum(cluster_array) / len(cluster_array)


# remember try and catch
# remember do while
# 4 points after the dot at print

EPSILON = 0.001
# iter value
iter = 200  # the default value
# the new value if one was entered
if len(argv) > 3:
    iter = int(argv[2])

# reading the file, compute N and the array of the dots
data_file = open(argv[-1], "r")
N = 0
dots_arr = []
# reading line by line (dot by dot)
line = data_file.readline()
while line != "":
    # print("the line is: " + line)
    # print(line.split(","))
    dots_arr.append([float(x) for x in line.split(",")])
    line = data_file.readline()
    N += 1
data_file.close()
D = len(dots_arr[0])  # the dimension of the dots

# check inputs
K = int(argv[1])
if K <= 1 or K >= N:
    raise Exception("Invalid number of clusters!")
if iter <= 1 or iter >= 1000 or iter >= N:
    raise Exception("Invalid maximum iteration")

# main
old_centroids = []
for i in range(K):
    old_centroids.append((dots_arr[i], []))
counter = 0
while True:
    new_centroids = []
    counter += 1
    # check if we finised the iteration
    if counter == iter:
        break
    # assign every dot to the closest cluster
    for i in range(N):
        add_to_cluster(dots_arr[i], old_centroids)
    # update the centorid
    for i in range(K):
        new_centroids.append((compute_centroid(old_centroids), []))

    # if delta of all the dots smaller than epsilon
    if check_delta_cenroids(old_centroids, new_centroids):
        break

    # update old cenroids array
    temp = old_centroids
    old_centroids = new_centroids
    del temp

# printing the K centroids
for k in range(K):
    for d in range(D):
        print("%.4f, " % old_centroids[k][d], end="")
    print()
