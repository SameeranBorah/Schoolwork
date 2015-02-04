;; scheme tictactoe homework
;; name: John F. Lake, Jr.	
;; date: 3 FEB 2015

(load-from-path "/afs/nd.edu/user37/cmc/Public/cse332_sp15/scheme_tictactoe/paradigms_ttt.scm")
(use-modules (ice-9 paradigms_ttt))
(use-modules (ice-9 debugging traps) (ice-9 debugging trace))

;; REPLACE WITH YOUR FUNCTIONS FROM A PREVIOUS HOMEWORK:
;;  greatest
;;  positionof
;;  value

;;This makes it easier to use the sum*-g function.
;;Simply invert the pair? function, to see if the item in question is an atom or not.
(define (atom? x) (not (pair? x)))

;;MY FUNCTIONS, from older scheme dailes:
;; greatest
;; return the greatest value in a tup, e.g., (1 3 2) -> 3
(define greatest
	(lambda (tup)
		(cond
			;;If the tup is null, return 0:
			((null? tup) 0)
	
			;;Check and see if the cdr is a number, so you can compare it with the car: 
			((number? (cdr tup)) 

				;;Return the value that's greater:
				(cond
					((> (car tup) (cdr tup)) (car tup))
					(else (cdr tup))	
				)
			)


			;;If it's not a number, see if the car is greater than the other values and recurse on the cdr:
			(else 
				(cond
					((> (car tup) (greatest (cdr tup))) (car tup))
					(else (greatest (cdr tup)))
				)

			)
		)			
	)
) 


;; positionof
;; you may assume that the given tup actually contains n
;; e.g., (positionof 23 (1 52 23 9)) -> 3
(define positionof
	(lambda (n tup)
		(cond
			;;Check and see if n is equal to the car.  If it is, return 1.   
			((eq? (car tup) n) 1)

			;;Otherwise, go to the next item in the list and add1 to the position that will be returned: 
			(else (+ 1 (positionof n (cdr tup))))
		)
	)
) 

;; value
;; given a game state, return the value of that state:
;; 10 if it's a win
;; -10 if it's a loss
;; 0 if it is either a draw or not an ending state
(define value
	(lambda (p gs)
		(cond
			;;If it's a win for you, return 10.
			((win? p gs) 10)

			;;If it's a win for them, return -10. 
			((win? (other p) gs) -10)
			
			;;Return 0 if it's not a win or loss:
			(else 0);
		)	
	)
)



;;LAKE: This is my sum*-g function, which passes in a function, the player, and the tree tuple:
(define sum*-g
	(lambda (func p ttup)
   		(cond 
			;; If the tree tup is empty, return 0.
			((null? ttup) 0)	


			;;If the car is an atom, it means this is a lat; return the value of it: 
			((atom? (car ttup)) (func p ttup))

			;;If the cdr is null, return the value from the car, or the sum of the list that happens to be the car:
			((null? (cdr ttup)) 
				(cond 
					;;If it's a lat, simply return the value.
					((atom? (car ttup)) (func p ttup)) 
					
					;;If it's NOT, it means it's a subtree and you need to recursively call it:
					(else (sum*-g func p (car ttup)))
				)
			)


			;;If the cdr is NOT null, return the value from the node plus the value from the cdr. 
			(else
				(cond
					;;If the car is a lat, add it to the sum of the cdr. 
					((atom? (car (car ttup))) (+ (func p (car ttup)) (sum*-g func p (cdr ttup))))

					;;Otherwise, recurse and add the sum of the car to the sum of the cdr.
					(else 
						(+ (sum*-g func p (car ttup)) (sum*-g func p (cdr ttup)))						
					)
				) 
			)
 		)
	)
)


;;This is a function which returns the move associated with a particular index: 
(define getValAt
	(lambda (count pos lat)
		(cond
			;;If count is equal to the position, return whatever is at that parent node: 
			((eq? pos count) (car (car lat)))


			;;Otherwise; increment count and move through the subtrees: 
			(else
				(getValAt (+ 1 count) pos (cdr lat))
			)
		)
	)
)


;; LAKE: sumSubtrees is a function that prints out the "values" associated with each subtree
(define sumSubtrees
	(lambda (p tree)
		(cond 
			;; If the rest of the cdr of the tree is null, only list the first part of the cdr
			((null? (cdr (cdr tree))) (list (sum*-g value p  (car (cdr tree))))) 


			;; Otherwise, return a list of the sum of the first subtree (the car of the cdr) and the recursive call to the other subtrees
			(else (cons (sum*-g value p (car (cdr tree))) (sumSubtrees p (cons (car tree) (cdr (cdr tree))))))
		)
	)
)



;; MODIFY this function so that given the game tree 
;; (where the current situation is at the root),
;; it returns the recommendation for the next move
;; LAKE: This function lets the user know the exact path to choose for a given game: 
(define nextmove
	(lambda (p gt)
		(cond
			;;If the cdr is null, it means you only have one choice, the parent: 
			((null? (cdr gt)) (car gt)) 


			;;Otherwise:
			(else
				;;Return the lat of the winning move: 
				;;I made 2 extra functions to help me get the particular value:
				(getValAt 0 (positionof (greatest (sumSubtrees p gt)) (sumSubtrees p gt)) gt)	
				
			)	
		)
	)
)
		


;; onegametree is defined in paradigms_ttt
;; be sure to look at that file!
;; what is the current game situation?
(display "Current State:     ")
(display (car (onegametree)))
(display "\n")

;; test of nextmove, where should we go next?
(display "Recommended Move:  ")
(display (nextmove 'x (onegametree)))
(display "\n")

;; correct output:
;;   $ guile tictactoe.scm
;;   Current State:     (x o x o o e e x e)
;;   Recommended Move:  (x o x o o x e x e)

