# coding=utf-8
import os


def printTree(file_path, depth=0):
    if not os.path.isdir(file_path):
        print(file_path+" is not a directory!")
        return
    files = os.listdir(file_path)
    for f in files:
        if not f.startswith('.'):
            sub_file_path = os.path.join(file_path, f)
            is_dir = os.path.isdir(sub_file_path)
            if is_dir or f.endswith('java'):
                print("| " * depth + "+--" + f)
            if is_dir:
                printTree(sub_file_path, depth+1)
                print("| " * depth)


# printTree('/Users/megvii/GitParent/FingerprintUnlockAp/app/src/main/java', 0)
# printTree('../time')

def quick_sort(array):
    return array if len(array) < 1 else quick_sort([item for item in array[1:] if item <= array[0]]) + [array[0]] + quick_sort([item for item in array[1:] if item > array[0]])


def quick_sort(array, direct, depth):
    if len(array) > 0:
        print("  "*depth+direct)
        print("  "*depth, end='')
        print(array)
        print(" ")
    return array if len(array) < 1 else quick_sort([item for item in array[1:] if item <= array[0]], 'left', depth+1) + [array[0]] + quick_sort([item for item in array[1:] if item > array[0]], 'right', depth+1)


quick_sort([2, 5, 9, 3, 7, 1, 5], 'start', 0)
#返回[1, 2, 3, 5, 5, 7, 9]

# a=[1, 2, 3, 5, 5, 7, 9]
# for x in range(len(a)):
#     print(a[x])
