var sname = "clevel";
window.onload = () =>
{
    let clevel = localStorage.getItem(sname);
    if (clevel == null) {
        clevel = "0";
    }
    document.getElementById("chorgorloth").value = clevel;
}
var numReg = /^\d+$/;
var expReg = /^(\d+)e(\d+)$/;

var parseNum = (str) => {
    let numReg = /^\d+$/;
    let expReg = /^(\d+)e(\d+)$/;
    let expReg2 = /^(\d+)\.(\d*)e(\d+)$/;
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

var chorgorlothEffect = (cost, level) => {
    let exp19 = 19n ** level;
    let exp20 = 20n ** level;
    return cost - cost * (exp20 - exp19) / exp20;
};

class AncientCosts {
    static expThresholds = [1101n, 1440n, 1498n, 2880n, 3743n, 18715n, 18715n];
    
    static exponentialRaw(level) {
        let exp = 13n;
        let ret = 0n;
        for (let i = 0; i < this.expThresholds.length; ++i) {
            let th = this.expThresholds[i];
            if (level <= th) {
                ret += 2n ** exp;
                return ret;
            }
            ret += 2n ** th;
            --exp;
        }
        return ret + (2n ** exp);
    }

    static exponential(level, clevel) {
        return chorgorlothEffect(this.exponentialRaw(level), clevel);
    }

    static juggernautRaw(level) {
        let s = sqrt(level);
        return level * level * s * 2n / 5n + level * s / 2n + s / 8n;
    }
    
    static juggernaut(level, clevel) {
        return chorgorlothEffect(this.juggernautRaw(level), clevel);
    }

    static mammonRaw(level) {
        return level * (level + 1n) * 4n;
    }

    static mammon(level, clevel) {
        return chorgorlothEffect(this.mammonRaw(level), clevel);
    }
};

var damageBonus = (juggernaut, mammon) => {
    return juggernaut * (mammon ** 3n);
};

class AncientLimits {
    static calcLimit(func) {
        let max = 2n;
        while (func(max)) {
            max *= max;
        }
        return binarySearch(func, 0n, max);
    }

    static exponential(souls, clevel) {
        let f = (n) => {
            return AncientCosts.exponential(n, clevel) <= souls;
        };
        return this.calcLimit(f);
    }
    static juggernaut(souls, clevel) {
        let f = (n) => {
            return AncientCosts.juggernaut(n, clevel) <= souls;
        };
        return this.calcLimit(f);
    }
    static mammon(souls, clevel) {
        let f = (n) => {
            return AncientCosts.mammon(n, clevel) <= souls;
        };
        return this.calcLimit(f);
    }
};

var damage = (juggernaut, souls, clevel) => {
    let a = AncientCosts.juggernaut(juggernaut, clevel);
    return damageBonus(juggernaut, AncientLimits.mammon(souls - a, clevel));
};

var min = (a, b) => {
    return a < b ? a : b;
}

var fibSearch = (right, souls, clevel) => {
    let inner = (x0, x1, x2, x3) => {
        let y1 = 0n;
        let y2 = 0n;
        if (right <= x3) {
            y1 = damage(x1, souls, clevel);
            y2 = damage(x2, souls, clevel);
        } else {
            before = inner(x0, x2, x3, x2 + x3);
            x0 = before[2];
            if (before[0]) {
                x1 = before[3];
                x2 = before[2] + x2;
                y1 = before[1];
                y2 = damage(x2, souls, clevel);
            } else {
                x1 = before[2] + x1;
                x2 = before[3];
                y1 = damage(x1, souls, clevel);
                y2 = before[1];
            }
            x3 = before[4];
        }
        if (!(x0 < x1 && x1 < x2 && x2 < x3)) {
            throw new Error();
        }
        if (y1 < y2) {
            return [true, y2, x1, x2, x3];
        } else {
            return [false, y1, x0, x1, x2];
        }
    };
    return inner(0n, 1n, 2n, 3n)[3];
};

var run = () => {
    let start = performance.now()
    document.getElementById("result").innerText = "計算中…";
    let clevel = BigInt(document.getElementById("chorgorloth").value);
    console.log()
    let soulsRaw = document.getElementById("soul").value;
    let souls = parseNum(soulsRaw);
    localStorage.setItem(sname, clevel);
    let expLevel = AncientLimits.exponential(souls, clevel);
    souls -= AncientCosts.exponential(expLevel, clevel);
    let juggernautLevel = fibSearch(AncientLimits.juggernaut(souls, clevel), souls, clevel);
    souls -= AncientCosts.juggernaut(juggernautLevel, clevel);
    let mammonLevel = AncientLimits.mammon(souls, clevel);
    souls -= AncientCosts.mammon(mammonLevel, clevel);
    let end = performance.now();
    document.getElementById("chronos").innerText = min(expLevel, AncientCosts.expThresholds[0]);
    document.getElementById("vaagur").innerText = min(expLevel, AncientCosts.expThresholds[1]);
    document.getElementById("kumawakamaru").innerText = min(expLevel, AncientCosts.expThresholds[2]);
    document.getElementById("atman").innerText = min(expLevel, AncientCosts.expThresholds[3]);
    document.getElementById("dogcog").innerText = min(expLevel, AncientCosts.expThresholds[4]);
    document.getElementById("bubos").innerText = min(expLevel, AncientCosts.expThresholds[5]);
    document.getElementById("dora").innerText = min(expLevel, AncientCosts.expThresholds[6]);
    document.getElementById("skills").innerText = expLevel;
    document.getElementById("juggernaut").innerText = expStr(juggernautLevel);
    document.getElementById("mammon").innerText = expStr(mammonLevel);
    document.getElementById("rest").innerText = expStr(souls);
    document.getElementById("result").innerText = "計算時間" + (end - start) +"ms";
}