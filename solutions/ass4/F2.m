## X is a square matrix
function Y = F2 (X)

k = 2;
n = rows (X) / k;

## Partitioning
Xtl = X (    1 : n  , 1 : n); Xtr = X (    1 : n  , n + 1 : end);
Xbl = X (n + 1 : end, 1 : n); Xbr = X (n + 1 : end, n + 1 : end);

## Multiplicating with I on the left
for r = 1 : n
    for c = 1 : n
	Ytl (r, c) = Xtl (r, c) + Xbl (r, c); Ytr (r, c) = Xtr (r, c) + Xbr (r, c);
	Ybl (r, c) = Xtl (r, c) - Xbl (r, c); Ybr (r, c) = Xtr (r, c) - Xbr (r, c);
    end
end

## Multiplicating with I on the right
for r = 1 : n
    for c = 1 : n
	Xtl (r, c) = Ytl (r, c) + Ytr (r, c); Xtr (r, c) = Ytl (r, c) - Ytr (r, c);
	Xbl (r, c) = Ybl (r, c) + Ybr (r, c); Xbr (r, c) = Ybl (r, c) - Ybr (r, c);
    end
end

## Multiplicating with D on the left and right
d = D (k, n);
for r = 1 : n
    for c = 1 : n
	Ytl (r, c) =         d (r, r) * Xtl (r, c) * d (c, c); Ytr (r, c) =         d (r, r) * Xtr (r, c) * d (c + n, c + n);
	Ybl (r, c) = d (r + n, r + n) * Xbl (r, c) * d (c, c); Ybr (r, c) = d (r + n, r + n) * Xbr (r, c) * d (c + n, c + n);
    end
end

## Multiplicating with Kronecker product on the left
KP = F (n);
Xtl = KP * Ytl; Xtr = KP * Ytr;
Xbl = KP * Ybl; Xbr = KP * Ybr;

## Multiplicating with Kronecker product on the right
Xtl = Xtl * KP; Xtr = Xtr * KP;
Xbl = Xbl * KP; Xbr = Xbr * KP;

## Multiplicating with the permutation matrix on the left
p = P (n * k, n);
ptl = p (    1 : n  , 1 : n); ptr = p (    1 : n  , n + 1 : end);
pbl = p (n + 1 : end, 1 : n); pbr = p (n + 1 : end, n + 1 : end);
Ytl = ptl * Xtl + ptr * Xbl; Ytr = ptl * Xtr + ptr * Xbr;
Ybl = pbl * Xtl + pbr * Xbl; Ybr = pbl * Xtr + pbr * Xbr;

## Multiplicating with the permutation matrix on the right
pT = p';
pTtl = pT (    1 : n  , 1 : n); pTtr = pT (    1 : n  , n + 1 : end);
pTbl = pT (n + 1 : end, 1 : n); pTbr = pT (n + 1 : end, n + 1 : end);
Xtl = Ytl * pTtl + Ytr * pTbl; Xtr = Ytl * pTtr + Ytr * pTbr;
Xbl = Ybl * pTtl + Ybr * pTbl; Xbr = Ybl * pTtr + Ybr * pTbr;

Y = zeros (n * k);
Y (    1 : n  , 1 : n) = Xtl; Y (    1 : n  , n + 1 : end) = Xtr;
Y (n + 1 : end, 1 : n) = Xbl; Y (n + 1 : end, n + 1 : end) = Xbr;
