#!/bin/bash




input=1
creation=1

coorFlag=0
zoomFlag=0
colorFlag=0
outputFlag=0
sizeFlag=0

# echo $input
while [ $input != 0 ]

do
    echo "Welcome to fractal generator, type in [1] for fractal generation, type [0] for exit"
    read input
    # echo $input
    if [ $input == 0 ]; then
        echo "Quitting"
        exit 1
   
 
   elif [ $input == 1 ]; then
        
        while [ $creation != 0 ]
        do
        clear
        echo "Here are you options"
        echo "Press [1] to input your X and Y coordinates"
        echo " [2] to input your zoom"
        echo " [3] for color mapping"
        echo " [4] for output file name"
        echo " [5] for size of fractal"
        echo " [6] for execution of fractal code"
        echo " [0] for exit"
        read creation
        
   

         
        if [ $creation == 1 ]; then
                echo "X val:"
                read X
                echo "Y val: "
                read Y
                echo "all done"
                coorFlag=1
        fi
        if [ $creation == 2 ]; then
            echo "Enter your zoom"
            read Zoom
            echo "all done"
            zoomFlag=1
        fi
        
        if [ $creation == 3 ]; then
            echo "Enter the color frame"
            read color
            #echo "Enter red scale (0-1)"
            #read red
            #echo "Enter green scale (0-1)"
            #read green
            #echo "Enter blue scale (0-1)"
            #read blue
            #echo "all done"
            colorFlag=1
        fi
        
        
        if [ $creation == 0 ]; then
            echo "quitting "
            exit 2
            
        fi
        
        if [ $creation == 4 ]; then
            echo "what do you want the name of the output file to be?"
            read name
            outputFlag=1
        fi
        
        if [ $creation == 5 ]; then
            echo "what do you want the size of the fractal to be?"
            read size
            sizeFlag=1
        fi
        
        
        if [ $creation == 6 ]; then
            echo "Creating"
            ARG=""
            # echo " Flags are $coorFlag $zoomFlag $colorFlag $outputFlag"
            # echo $coorFlag -2
            
            if [ $coorFlag == 1 ]; then
                ARG=" -c ${X} ${Y} "
            fi
            
            if [ $zoomFlag == 1 ]; then
                 ARG=" ${ARG} -w ${Zoom} "
            fi
               
            if [ $colorFlag == 1 ]; then
                 ARG=" ${ARG} -s ${color} "
            fi
            
            if [ $sizeFlag == 1 ]; then
                 ARG=" ${ARG} -n ${size} "
            fi
            
           
            
            # echo "The command will be ./fractal $ARG"
            
            eval "./fractal  ${ARG}"
            
             if [ $outputFlag == 1 ]; then
                 ARG=" ${ARG} -n ${name} "
                 ffmpeg "-hide_banner" "-loglevel" "fatal" -i "fractal.ppm" "${name}.png"
            
            else
                ffmpeg "-hide_banner" "-loglevel" "fatal" -i "fractal.ppm" "fractal.png"
            
            
            fi
            rm fractal.ppm
            
            echo "Make another?"
            
            
            
        fi
        
        
        done  
    
    
    fi   
done   