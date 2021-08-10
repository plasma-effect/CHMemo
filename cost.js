var binarySearch = (func, min, max) => {
    while (max - min > 1n) {
        let mid = (min + max) / 2n;
        if (func(mid)) {
            min = mid;
        } else {
            max = mid;
        }
    }
    return min;
};

var sqrt = (num) => {
    return binarySearch((n) => { return n * n <= num; }, 0n, num);
};