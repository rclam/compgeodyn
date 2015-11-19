      program neighbor

!$ use omp_lib               ! use the OpenMP library

!***  Declare variables
      implicit none
      integer, parameter                  :: n = 160, &
                                             m = 10000

      real*8, dimension(:,:), allocatable :: a, b
      real*8                              :: dt, xk, xk2
      integer                             :: mts, icount1, icount2, icountr
      integer                             :: i, j, k, j_update

      write (*,*)

!***  Get the number of Threads (Method 1 with pragma OPENMP)
#ifdef _OPENMP
      mts = omp_get_max_threads()
      write (*,'(A,I2)') 'Method 1 :: Number of Threads is ', mts
#endif

!***  Get the number of Threads (Method 2 with special comment !$)
!$     mts = omp_get_max_threads()
!$     write (*,'(A,I2)') 'Method 2 :: Number of Threads is ', mts
write (*,*)

!***  Allocate data
      allocate(a(n,n), b(n,n))

!***  Reset a and b
      do j=1, n
        do i=1, n
          a(i,j) = 0.
          b(i,j) = 0.
        enddo
      enddo

!***  Preset a
      do i=1, n
        do j=1, n
          do k=1, m
            a(j,i) = a(j,i) + real(i*j) / real(i+j+k)
          enddo
        enddo
      enddo

!***  Start the counter
      call system_clock(icount1, icountr)

!***  Calculate b (and j_update)

!***  Parallel Region
!!!!  Start your parallel region here
!$omp ... default(none)             &
!$omp          private(i, j, k, xk, xk2) &
!$omp          shared(a, b, j_update)

!***  Initialize j_update
!!!!  Initialize j_update with one OpenMP thread
!$omp ...
      j_update = 0
!$omp end ...

!***  OpenMP worksharing
!!!!  Try different scheduling options: static, dynamic, guided
!$omp do schedule(...)
      do i=2, n-1
        do j=2, i
!!!!  Update j_update with one OpenMP thread
!$omp ...
          j_update = j_update + 1
!$omp end ...
          do k=1, m
            xk     = real(k)
            xk2    = xk * xk
            b(j,i) = b(j,i)                                 + &
                     a(j  ,i-1) / xk   +  a(j  ,i+1) / xk   + &
                     a(j-1,i  ) / xk   +  a(j+1,i  ) / xk   + &
                     a(j-1,i-1) / xk2  +  a(j+1,i+1) / xk2  + &
                     a(j-1,i+1) / xk2  +  a(j+1,i-1) / xk2
          enddo
        enddo
      enddo
!$omp end parallel

!***  Stop the counter and calculate the time
      call system_clock(icount2)
      dt = (real(icount2) - real(icount1)) / real(icountr)

!***  Print the output
      write (*,'(a,2(1x,es12.5),2x, a,i8,2x, a,es9.3,a)') &
        'b(2,2), b(n-1,n-1) = ',  b(2,2), b(n-1,n-1), &
        'Number of j updates = ', j_update,           &
        'time = ',                dt, 's'

      end
