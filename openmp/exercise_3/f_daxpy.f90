      program calc_daxpy

!!!! Use the proper OpenMP module here
!$    use ...

!***  Declare variables
      implicit none
      real*8    :: dt, memory_gb
      integer   :: mts, itrial, icount1, icount2, icountr
      integer*8 :: i, n

      real*8, dimension(:), allocatable :: a, x, b, y

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

      do itrial=1, 3                       ! Loop over different n

        n      = 10_8**(itrial+5)          ! Number of iterations

        allocate (a(n), b(n), x(n), y(n))  ! Allocate vectors

        do i=1, n
          a(i) = sqrt(real(i))
          b(i) = sqrt(real(i+1))
          x(i) = sqrt(real(i+2))
        enddo

        memory_gb = 3. * real(n) * 8. / 1024.**3

!*** Start the counter
        call system_clock(icount1, icountr)

!***  Loop over n
!!!!  Parallelize this loop with OpenMP
!$omp ...
        do i=1, n
          y(i) = a(i) * x(i) + b(i)
        enddo

!***  Stop the counter and calculate the time
        call system_clock(icount2)
        dt = (real(icount2) - real(icount1)) / real(icountr)

        deallocate (a, b, x, y)            ! Deallocate vectors

!***  Print the output
        write (*,'(a,i12,5x, a,f5.2,a,5x, a,es9.3,a)')  &
          'Length of vectors :', n,                     &
          'Total amount of memory : ', memory_gb, 'GB', &
          'time = ', dt, 's'

      enddo

end
