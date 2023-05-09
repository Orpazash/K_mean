from sys import argv

EPSILON = 0.001

def compute_distance(dot1, dot2):  # dot1 and dot2 are arrays
    coordinates_square = []
    summ = 0

    for i in range(len(dot1)):
        coordinates_square.append(pow((dot2[i] - dot1[i]), 2))

    for num in coordinates_square:
        summ += num

    return pow(summ, 0.5)


"""
  gets dot and centroid list, adds the dot to the right cluster, returns None
  !! the list old_centroids is a list of tuples -> (centroid_0, cluster_0 array), where the cluster arrays are empty
"""
def add_to_cluster(dot: list, old_centroids: list):
    curr_min = float('inf')
    chosen_centroid = None

    for centroid in old_centroids:
        curr_dist = compute_distance(dot, centroid[0])  # --> centroid[0] is the u_k of the cluster
        if curr_min > curr_dist:
            chosen_centroid = centroid
            curr_min = curr_dist

    chosen_centroid[1].append(dot)
    return None

def check_delta_cenroids(old_centroids: list, new_centroids: list):  # returns true if delta smaller than epsilon
    for i in range(0, len(old_centroids)):  # CAN CHANGE TO K
        if compute_distance(new_centroids[i][0], old_centroids[i][0]) > EPSILON:
            return False
    return True


def compute_centroid(cluster_array: list):
    new_centroid = []
    for d in range(D):
        total = 0
        for i in range(len(cluster_array)):
            total += cluster_array[i][d]
        new_centroid.append(total / len(cluster_array))
    return new_centroid


def read_file(N: int, dots_arr: list):
    # reading the file, compute N and the array of the dots
    data_file = open(argv[-1], "r")
    # reading line by line (dot by dot)
    line = data_file.readline()
    while line != "":
        dots_arr.append([float(x) for x in line.split(",")])
        line = data_file.readline()
        N += 1
    data_file.close()
    return N



def check_inputs(K, iter_num):
    valid_input = True

    # check if K or not in the range
    if K <= 1 or K >= N:
        print("Invalid number of clusters!")
        valid_input = False

    # check if iter is not in the range
    if iter_num <= 1 or iter_num >= 1000:
        print("Invalid maximum iteration!")
        valid_input = False

    return valid_input


# save inputs
dots_arr = []
N = read_file(0, dots_arr)
D = len(dots_arr[0])  # the dimension of the dots
# according to the forum we can assume the inputs are of type int
K = int(argv[1])
iter_num = 200  # iter default value
if len(argv) > 3:
    iter_num = int(argv[2])

# only if the input is valid we continue
if check_inputs(K, iter_num):
    # noinspection PyBroadException
    try:
        old_centroids = []
        for i in range(K):
            old_centroids.append((dots_arr[i], []))
        counter = 0
        while True:
            new_centroids = []
            # check if we finished the iteration
            if counter == iter_num:
                break
            # assign every dot to the closest cluster
            for i in range(N):
                add_to_cluster(dots_arr[i], old_centroids)
            # update the centroid
            for i in range(K):
                new_centroids.append((compute_centroid(old_centroids[i][1]), []))
            # if delta of all the dots smaller than epsilon
            if check_delta_cenroids(old_centroids, new_centroids):
                break
            # update old centroids array
            temp = old_centroids
            old_centroids = new_centroids
            del temp
            counter += 1
        # printing the K centroids
        for k in range(K):
            print(",".join(["%.4f" % old_centroids[k][0][d] for d in range(D)]))
    except:
        print("An Error Has Occurred")
