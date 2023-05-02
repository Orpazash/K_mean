# skadlkajdlaj
# lkjlkajsd

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


def check_delta_cenroids(old_centroids, new_centroids):  # returns true if delta smaller than epsilon
    for i in range(0, len(old_centroids)):  # CAN CHANGE TO K
        if compute_distance(new_centroids[i][0], old_centroids[i][0]) > 0.001:
            return False

    return True


def compute_centroid(cluster_array):
    return None

# remember try and catch
# remember do while
# 4 points after the dot at print
#

######check add to cluster func######
# dot_tryy = [3.0, 6.0]
# centroids_try = [([5.0,6.0],[]),([14.0,6.0],[]),([2.0,6.0],[])]
# add_to_cluster(dot_tryy,centroids_try)
# print(centroids_try)

######check check delta centroid func ######
# old_centroids_try = [([5.0, 6.0], []), ([14.0, 6.0], []), ([2.00051, 6.0], [])]
# new_centroids_try = [([5.0, 6.0], []), ([14.0, 6.0], []), ([2.0, 6.0], [])]
# print(check_delta_cenroids(old_centroids_try, new_centroids_try))
