% X is a square matrix
function Y = F2 (X)

k = 2;
n = rows (X) / k;

% Partitioning
Xtl = X (    1 : n  , 1 : n); Xtr = X (    1 : n  ,     n : end);
Xbl = X (n + 1 : end, 1 : n); Xbr = X (n + 1 : end, n + 1 : end);

% Multiplicating with I on the left
for r = 1 : n
    for c = 1 : n
	Ytl (r, c) = Xtl (r, c) + Xbl (r, c); Ytr (r, c) = Xtr (r, c) + Xbr (r, c);
	Ybl (r, c) = Xtl (r, c) - Xbl (r, c); Ybr (r, c) = Xtr (r, c) - Xbr (r, c);
    end
end

% Multiplicating with I on the right
for r = 1 : n
    for c = 1 : n
	Xtl (r, c) = Ytl (r, c) + Ytr (r, c); Xtr (r, c) = Ytl (r, c) - Ytr (r, c);
	Xbl (r, c) = Ybl (r, c) + Ybr (r, c); Xbr (r, c) = Ybl (r, c) - Ybr (r, c);
    end
end

d = D (k, n);
% Multiplicating with D on the left and right
for r = 1 : n
    for c = 1 : n
	Ytl (r, c) =         d (r, r) * Xtl (r, c) * d (r, r); Ytr (r, c) =         d (r, r) * Xtr (r, c) * d (r + n, r + n);
	Ybl (r, c) = d (r + n, r + n) * Xbl (r, c) * d (r, r); Ybr (r, c) = d (r + n, r + n) * Xbr (r, c) * d (r + n, r + n);
    end
end

KP = kron (eye (k), F (n));
KP_tl = KP (    1 : n  ,     1 : n);
KP_br = KP (n + 1 : end, n + 1 : end);
% Multiplicating with Kronecker product on the left
Xtl = KP_tl * Ytl; Xtr = KP_tl * Ytr;
Xbl = KP_br * Ybl; Xbr = KP_br * Ybr;

% Multiplicating with Kronecker product on the right
Xtl = Xtl * KP_tl; Xtr = Xtr * KP_br;
Xbl = Xbl * KP_tl; Xbr = Xbr * KP_br;

% Multiplicating with the permutation matrix on the left
for i = 1 : k
    for j = i : k : n * k
	if (j <= n)
	    Ytl (j    , :) = Xtl (j, :)    ; Ytr (j    , :) = Xtr (j    , :);
	else
	    Ybl (j % n, :) = Xbl (j % n, :); Ybr (j % n, :) = Xbr (j % n, :);
	end
    end
end

% Multiplicating with the transpose of the permutation matrix on the right
for i = 1 : k
    for j = i : k : n * k
	if (j <= n)
	    Xtl (:, j    ) = Ytl (:, j)    ; Xtr (:, j    ) = Ytr (:, j    );
	else
	    Xbl (:, j % n) = Ybl (:, j % n); Xbr (:, j % n) = Ybr (:, j % n);
	end
    end
end
