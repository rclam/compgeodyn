      program calc_pi

!!!! Use the proper OpenMP module here

!***  Declare variables
      implicit none
      real*8    :: deltax, area, x, xn, pi, pi_exact, dt
      integer   :: its, mts, itrial, icount1, icount2, icountr
      integer*8 :: i, n

      write (*,*)

!***  Get the number of Threads (Method 1 with pragma OPENMP)
#ifdef _OPENMP
!!!!  get mps from the correct function call
      mts = ...
      write (*,'(A,I2)') 'Method 1 :: Number of Threads is ', mts
#endif

!***  Get the number of Threads (Method 2 with special comment !$)
!$    mts = omp_get_max_threads()
!$    write (*,'(A,I2)') 'Method 2 :: Number of Threads is ', mts


!***  Print the Threads Numbers
!$omp parallel private(its)
!!!!  Print the thread numbers, use the omp_get_thread_num function
!$    its = ...
      write (*,'(12x,a,5x,i4)') 'This is Thread', its
!$omp end parallel

      pi_exact = 2._8 * acos(0._8)      ! Exact value of pi

      do itrial=1, 4                    ! Loop over different n

        n      = 10_8**(itrial+5)       ! Number of iterations
        deltax = 2._8 / real(n,kind=8)
        area   = 0.                     ! Reset the area

!*** Start the counter
        call system_clock(icount1, icountr)

!***  Loop over n
!!!!  Finish the parallel do, use a reduction
!$omp parallel do reduction(...) &
!$omp             default(none) private(...) shared (...)
        do i=1, n
          x    = -1._8 + real(i,kind=8) * deltax
          area = area + sqrt(1._8 - x*x) * deltax
        enddo

        pi = 2._8 * area                ! Calculate pi from area

!*** Stop the counter and calculate the time
        call system_clock(icount2)
        dt = (real(icount2) - real(icount1)) / real(icountr)

!***  Print the output
        write (*,'(a,i12,5x, a,f22.20,5x, a,es12.5,5x, a,es9.3,a)') &
          'Number of intervals :', n,                               &
          'pi = ',                 pi,                              &
          'delta = ',              pi - pi_exact,                   &
          'time = ',               dt, 's'

      enddo

end
