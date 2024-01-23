practice_oneapi

[ test history ]

  2024.01.08
    - my computer is windows10
    - heap hahaha

  2024.01.10    
    - i love 'std'
    - i don't want to know 'typedef'
    - i don't want to know 'double pointer'
    - always full test
    - heap hahahaha

  2024.01.16
    - onedpl
      - target_include_directories()
        - "C:/Program Files (x86)/Intel/oneAPI/dpl/2022.3/include/"
        - #include <oneapi/dpl/random>

  2024.01.17 ~ 2024.01.23
    - onemkl
      - https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-link-line-advisor.html
        - target_compile_options()
          - "/Qmkl:sequential"
          - "/Qmkl-ilp64:sequential"
        - target_link_options()
          - "OpenCL.lib"
      - #include <oneapi/mkl.hpp>
        - for use namespace oneapi::mkl::###
      - #include <oneapi/mkl/rng/device.hpp>
        - for use namespace oneapi::mkl::rng::device
        - only used for q->parallel_for() inside.

  2024.01.23 ~ 
    - library pre-load ?
      