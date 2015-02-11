;; scheme daily homework 5
;; name: John F. Lake, Jr. 
;; date: 28 JAN 2015

;; sum*
(define sum*
	(lambda (ttup)
   		(cond 
			;; If the tree tup is empty, return 0.
			((null? ttup) 0)	


			;;If the cdr is null, return the value from the car, or the sum of the list that happens to be the car:
			((null? (cdr ttup)) 
				(cond 
					;;If it's a number, simply return the value.
					((number? (car ttup)) (car ttup)) 
					
					;;If it's a list, simply recurse to get its value.
					(else (sum* (car ttup)))
				)
			)


			;;If the cdr is NOT null, return the value from the node plus the value from the cdr. 
			(else
				(cond
					;;If the car is a number, add it to the sum of the cdr. 
					((number? (car ttup)) (+ (car ttup) (sum* (cdr ttup))))

					;;Otherwise, recurse and add the sum of the car to the sum of the cdr.
					(else 
						(+ (sum* (car ttup)) (sum* (cdr ttup)))						
					)
				) 
			)
 		)
	)
	;; currently always returns zero
	;; change it so that it returns the sum of every node in the tree
)

;; tests!
(display (sum* (list (list '5) (list))))
(display "\n")

(display (sum* (list (list '0) (list (list '0) (list (list '5) (list))) (list (list '0) (list (list '10) (list)))) ))
(display "\n")

(display (sum* (list (list '0) (list (list '0) (list (list '5) (list (list '7) (list)))) (list (list '0) (list (list '10) (list)))) ))
(display "\n")

(display (sum* (list (list '0) (list (list '0) (list (list '5) (list (list '7) (list)) (list (list '8) (list)))) (list (list '0) (list (list '10) (list)))) ))
(display "\n")

;; correct output:
;;   $ guile d5.scm
;;   5
;;   15
;;   22
;;   30

