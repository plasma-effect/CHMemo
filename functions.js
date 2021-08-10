var parseNum = (str) => {
    const numReg = /^\d+$/;
    const expReg = /^(\d+)e(\d+)$/;
    const expReg2 = /^(\d+)\.(\d*)e(\d+)$/;
    let numSoul = str.match(numReg);
    let expSoul = str.match(expReg);
    let expSoul2 = str.match(expReg2);
    if (numSoul != null) {
        return BigInt(soulsRaw);
    } else if (expSoul != null) {
        return BigInt(expSoul[1]) * (10n ** BigInt(expSoul[2]));
    } else if (expSoul2 != null) {
        let significant = BigInt(expSoul2[1]);
        let additional = BigInt(expSoul2[2].split('').reverse().join(''));
        let digit = BigInt(expSoul2[3]);
        while (digit > 0n && additional > 0n) {
            significant *= 10n;
            significant += additional % 10n;
            --digit;
            additional /= 10n;
        }
        return significant * (10n ** digit);
    }
    return null;
};

var expStr = (num) => {
    significant = 0n;
    digit = 0n;
    if (num == 0n) {
        return "0.000e0";
    }
    while (num >= 10n) {
        significant /= 10n;
        significant += (num % 10n) * 100n;
        ++digit;
        num /= 10n;
    }
    return num + "." + ("000" + significant).slice(-3) + "e" + digit;
};