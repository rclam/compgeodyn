      program do_print

!$    use omp_lib               ! use the OpenMP library

!***  Declare variables
      implicit none
      integer   :: mts, i, its1, its2, its5

      write (*,*)

!***  Get the number of Threads (Method 1 with pragma OPENMP)
#ifdef _OPENMP
      mts = omp_get_max_threads()
      write (*,'(A,I2)') 'Method 1 :: Number of Threads is ', mts
#endif

!***  Get the number of Threads (Method 2 with special comment !$)
!$    mts = omp_get_max_threads()
!$    write (*,'(A,I2)') 'Method 2 :: Number of Threads is ', mts


!$omp parallel default(none) private(its1, its2, its5)
!$    its1 = omp_get_thread_num()
      write (*,*) 'Print #1, its1 = ', its1

!$omp do private(i)
      do i=1, 5
!$      its2 = omp_get_thread_num()
        write (*,*) 'Print #2, its2 = ', its2
      enddo

      call printer_sub()

!$omp master
!$    its5 = omp_get_thread_num()
      write (*,*) 'Print #5, its5 = ', its5
!$omp end master

!$omp end parallel

      end


      subroutine printer_sub()

!$    use omp_lib               ! use the OpenMP library

      implicit none
      integer :: i, its3, its4

!$omp do
      do i=1, 3
!$      its3 = omp_get_thread_num()
        write (*,*) 'Print #3, its3 = ', its3
      enddo

      do i=1, 3
!$      its4 = omp_get_thread_num()
        write (*,*) 'Print #4, its4 = ', its4
      enddo

      end
