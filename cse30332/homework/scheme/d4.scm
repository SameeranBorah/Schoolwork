;; scheme daily homework 4
;; John F. Laks, Jr.
;; 28 Jan 2015

(load-from-path "/afs/nd.edu/user37/cmc/Public/cse332_sp15/scheme_dailies/d4/paradigms_d4.scm")
(use-modules (ice-9 paradigms_d4))

;; filterN
(define filterN
        (lambda (n m lat)
		(cond
			;;Check if the list is empty: 
			((null?  lat) '())
			
			;;Check if the first member of the list is a number. If it is, then operate on it.  Otherwise, skip it. 
			((number? (car lat))
				(cond
					;;If the number is equal to n or m, you include it in the output:
					((zero? (- (car lat) n)) (cons (car lat) (filterN n m (cdr lat))))
					((zero? (- (car lat) m)) (cons (car lat) (filterN n m (cdr lat))))

					;;If the number is between n and m (that is, n < number < m), then include it in the output: 
					((and (> (car lat) n) (< (car lat) m)) (cons (car lat) (filterN n m (cdr lat))))


					;;If the number falls outside of the required criteria, skip over it. 
					(else (filterN n m (cdr lat)))
				)
			)
			;;Don't process it if it's not a number
			(else (filterN n m (cdr lat)))
		)
	)
)
 
    ;; currently this function just returns the lat as it is given
    ;; change the function so that it returns /only/ the numbers
    ;; >= n and <= m
    ;; see below for examples...

;; tests!
(display (filterN 4 6 '(1 turkey 5 9 4 bacon 6 cheese)))
(display "\n")

(display (filterN 4 6 '(4 4 4 1 1 bacon 9 9 9 6 6 6 1 4 5)))
(display "\n")

;; correct output:
;;   $ guile d4.scm
;;   (5 4 6)
;;   (4 4 4 6 6 6 4 5)

