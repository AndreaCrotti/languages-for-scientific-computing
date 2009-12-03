function F2_test (max_power)

if (max_power <= 0)
    printf ("max_power has to be greater than 0\n");
    return
end

I = [];
T_fft2 = [];
T_f2 = [];

for i = 1 : max_power
    A = rand (10 ^ i);
    tic; R1 = fft2 (A); fft2_time = toc;
    tic; R2 = F2 (A)  ; f2_time = toc;
    printf ("Square matrix of size %lu:\n", 10 ^ i);
    printf ("\tfft2 = %f seconds\n", fft2_time);
    printf ("\t  f2 = %f seconds\n", f2_time);

    is_first = 1;
    for r = 1 : rows (A)
	for c = 1 : columns (A)
	    diff = abs (abs (R1 (r, c)) - abs (R2 (r, c)));
	    if (is_first)
		max = diff;
		is_first = 0;
	    else
		if (max < diff)
		    max = diff;
		end
	    end
	end
    end
    printf ("\tLargest difference: %g\n", max);

    I (i) = 10 ^ i;
    T_fft2 (:, i) = fft2_time;
    T_f2 (:, i) = f2_time;
end

plot (I, T_fft2, "b");
hold on;
plot (I, T_f2, "r");
legend ("ff2", "f2");
title ("The speed of fft2 and our f2");
xlabel ("Square matrix size");
ylabel ("Time of computation (s)");
