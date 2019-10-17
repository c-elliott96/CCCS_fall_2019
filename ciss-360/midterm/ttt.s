        .text
        .globl main

main:
        la      $a0, WELCOME    # print welcome statement
        li      $v0, 4          # print welcome statement
        syscall
        la      $a0, ENTER_N    # print ask for n statement
        li      $v0, 4          # print ask for n statement 
        syscall
        li      $v0, 5          # read int n 
        syscall
        move    $s0, $v0        # move $v0 into $s0 - n is now $s0
        
        mul     $s1, $s0, $s0   # $s1 = n * n 

        li      $t0, 0          # start of our for loop 
        move    $t1, $s1        # end of our loop is n * n

        li      $t3, 4          # t3 will be our incrementer for our array iteration
        li      $t4, 0          # what we will add t3 to for our array pointer

        la      $s2, ARR        # $s2 points to arr[0]
LOOP_01:        
                
                beq     $t0, $t1, EXIT_01 # if t0 == t1 break for loop 
                ######## body of for loop to fill memory with ' '                
                li      $t5, ' '
                sw      $t5, 0($s2)     # arr[i] = ' '
                addi    $t0, $t0, 1     # i++
                addi    $s2, $s2, 4     # address of pointer += 4
                j       LOOP_01

EXIT_01:

        ########################################################
        # at this point we have initialized our array for our board
        ########################################################
        li      $v0, 10
        syscall

        # now we need to print the board properly
        # How do we implement our forumla to calculate locations? 
        # don't worry about that yet, worry about properly printing the
        # board. 

        

        .data
WELCOME:  .asciiz "Let's play a game of tic-tac-toe.\n"
ENTER_N:  .asciiz "Enter n: "
ARR:    .word 0