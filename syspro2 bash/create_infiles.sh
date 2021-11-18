#!/bin/bash

if [ $# = 5 ];
then 
   
    echo  arguments were given correctly $#
    echo disease file : $1
    echo countries file : $2

    mkdir $3
    dir=$3
    filesPerDirectory=$4
    echo $filesPerDirectory
   
    flag=$(( 365  >= $filesPerDirectory ))
    echo flag is $flag
    
    numRecordsPerFile=$5

    #ftiaxnw ton pinaka DaysArray
    DaysArray=('01' '02' '03' '04' '05' '06' '07' '08' '09')
    for (( di=9; di<=29; di++ ))
    do
        # let var = ($di + 2)) 
        DaysArray[di]=$(( $di+1 ))
    done
    #test print to see if it is correct
    echo "test print to see if it is correct"
    for (( di=0; di<=29; di++ ))
    do
        echo ${DaysArray[di]}
    done
    
    

    #pinakas mhnwn
    MonthsArray=('01' '02' '03' '04' '05' '06' '07' '08' '09' '10' '11' '12')
    # flag2=$(( ${MonthsArray[10]} <= 12 ))
    # echo flag2 i wanna see $flag2

    dmindex=0;
    #pinakas DaysMonths=DD-MM-
    for (( di=0; di<=11; di++ ))
    do
        for (( dii=0; dii<=29; dii++ ))
        do
           DaysMonths[$dmindex]="${DaysArray[dii]}-${MonthsArray[di]}-"
           dmindex=$(($dmindex +1))
        done     
    done 
    #testpinakas DaysMonths
    # for (( i=0; i<$dmindex ; i++ ))
    # do 
    #     echo "date $i) ${DaysMonths[$i]}"
    # done

    
    echo "numRecordsPerFile=$numRecordsPerFile"
    
    echo " before loop id=$id"

    vindex=0; #virus index
    #pinakas virus xrhsimopoihtai viruses[RANDOM%7] (0 ME 6)
     for viruses in $(cat  $1); do 
        varray[vindex]=$viruses
        vindex=$(( vindex + 1 ))
     done

     for (( i=0; i<$vindex; i++)) do
        echo ${varray[i]}
     done
     echo "Viruses num= $(($vindex))" 
    #pinakas status xrhsimopoieitai status[RANDOM%2] (0 ME 1)
     status=("ENTER"  "EXIT") #0 gia enter 1 gia exit

     patients=$(( $filesPerDirectory *  $numRecordsPerFile )) 
     echo "$filesPerDirectory *  $numRecordsPerFile = $patients"
     patientmonozygo=$(( $patients % 2))
     #posoi patients xreiazonte , an einai zygos ari8mos tote patients=fpd*nrpf/2 alliws fpd*nrpf/2 +1
     if [ $patientmonozygo = 0 ]
     then
        patients=$(( $patients /  2)) 
     else
        patients=$(( $patients /  2))
        patients=$(( $patients +1 ))
     fi
     
     #echo "patients/2 || patients/2 +1 = $patients"

    # -----------------------------------------------------------------------------------
    id=1
    lettersA=('a' 'e' 'i' 'o' 'u' 'y') #RANDOM%5
    lettersB=('b' 'c' 'd' 'f' 'g' 'h' 'j' 'k' 'l' 'm' 'n' 'p' 'q' 'r' 's' 't' 'v' 'w' 'x' 'z') #RANDOM%19
    for Countries in $(cat  $2); do 
        echo country $Countries
        mkdir $dir/$Countries
            #edw 8a ftia3w th lista twn patients
         for (( j=0; j<$patients; j++)) do
            #dhmiourgia first name length apo 3 mexri 12 kai arxikopoihsh se keno string
            FnameLength=$(($RANDOM % 10))
            FnameLength=$(($FnameLength +3))
            fname=""
            for(( l=0; l<FnameLength; l++))
            do
                fwnien=$(( $l % 2 )) #an einai 0 einai fwnien ( lettersA ) alliws lettersB
                if [ $fwnien -eq 0 ]
                then
                    fname="$fname${lettersA[RANDOM%5]}"    
                else
                   fname="$fname${lettersB[RANDOM%19]}" 
                fi
            done
            #dhmiourgia last name length apo 3 mexri 12 kai arxikopoihsh se keno string
            LnameLength=$(($RANDOM % 10))
            LnameLength=$(($LnameLength +3))
            lname=""
            for(( l=0; l<LnameLength; l++))
            do
                fwnien=$(( $l % 2 )) #an einai 0 einai fwnien ( lettersA ) alliws lettersB
                if [ $fwnien -eq 0 ]
                then
                    lname="$lname${lettersA[RANDOM%5]}"    
                else
                   lname="$lname${lettersB[RANDOM%19]}" 
                fi
            done

            #ftiaxnw age

            age=$(($RANDOM % 120))
            age=$(($age + 1 ))
            # 8a gemisw symmetrika ton pinaka ton miso me kapoia atoma kai ton allo miso me ta idia atoma me random status kai stis 2 periptwseis
            virusi=${varray[RANDOM%7]}
            patientList[$j]="$id ${status[RANDOM%2]} $fname $lname $virusi $age"
            patientList[$j+$patients]="$id ${status[RANDOM%2]} $fname $lname $virusi $age"

            id=$(($id +1 ))
        done
        index=0
        for (( i=1; i<=$filesPerDirectory; i++)) do
            
            
            tdate=${DaysMonths[$RANDOM%360]}
            
            year=$(($RANDOM % 31))
            year=$(($year + 1990))
            
            tdate="$tdate$year"
            # echo $tdate
            touch $dir/$Countries/$tdate
            filevar="$dir/$Countries/$tdate"
            for(( newindex = 0; newindex<numRecordsPerFile; newindex++)) do
               echo "${patientList[index]}" >> $filevar
                index=$(($index +1))
            done 

        done
        
    done
    
    # Test  patient List ( iteration ) 
    # for ((i=0; i<$patients; i++))
    # do
    #     echo ${patientList[$i]}
    # done
    # -----------------------------------------------------------------------------------
   
     
    
    echo "type delete if you want to delete the folders and files in countries else type anything else ( testing ) " 
    read b;
    
    if [ "$b" = "delete" ]; 
    then
        echo you chose to delete everything
        for Countries in $(cat  countries); do 
            echo  deleting country $Countries
            rm -r $3/$Countries
        done
    else 
        echo "You chose to not delete anything"
    fi

else 
    echo $# were given and should be 5 try ./create_infiles.sh diseaseFile countriesFile input_dir numFilesPerDirectory numRecordsPerFile
fi