      program read_black

!$ use omp_lib               ! use the OpenMP library

!***  Declare variables
      implicit none
      integer, parameter                :: n = 100000000
      real*8, dimension(:), allocatable :: a
      real*8                            :: dt, error
      integer                           :: mts, icount1, icount2, icountr
      integer                           :: i, niter

      write (*,*)

!***  Get the number of Threads (Method 1 with pragma OPENMP)
#ifdef _OPENMP
      mts = omp_get_max_threads()
      write (*,'(A,I2)') 'Method 1 :: Number of Threads is ', mts
#endif

!***  Get the number of Threads (Method 2 with special comment !$)
!$    mts = omp_get_max_threads()
!$    write (*,'(A,I2)') 'Method 2 :: Number of Threads is ', mts
      write (*,*)

!***  Allocate and preset data
      allocate(a(n))
      do i=1, n-1, 2
        a(i)   = 0.
        a(i+1) = 1.
      enddo

!*** Start the counter
      call system_clock(icount1, icountr)

!***  Iteration Loop
      niter = 0
      do
!***  Increase iteration counter
        niter = niter + 1

!***  Update even elements
!!!!  Parallelize this loop
        do i=2, n, 2
          a(i) = 0.5 * (a(i) + a(i-1))
        enddo

!***  Update odd elements
!!!!  Parallelize this loop
        do i=1, n-1, 2
          a(i) = 0.5 * (a(i) + a(i+1))
        enddo

!***  Calculate error
        error = 0.
!!!!  Parallelize this loop, use a reduction
        do i=1, n-1
          error = error + abs(a(i) - a(i+1))
        enddo

!***  Print loop information
        write (*,'(a,i6,4x,a,es9.2)') 'Iteration : ', niter, 'error = ', error

!***  Exit loop, if error is small
        if (error < 1.) then
          exit
        endif
      enddo

!*** Stop the counter and calculate the time
      call system_clock(icount2)
      dt = (real(icount2) - real(icount1)) / real(icountr)

!***  Print the output
      write (*,'(a,i6,5x, a,es12.5,5x, a,es9.3,a)') &
        'Number of iterations :', niter,            &
        'error = ',              error,             &
        'time = ',               dt, 's'

end
