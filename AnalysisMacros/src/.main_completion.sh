_main() 
{
    local cur prev opts
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    opts="--help --mode --dname --run -FP -FCP -tCP -lFCP -aFCP -derThresh -LP -aAP -TEC -mu --muTrg --asym_cut --input"

    case "${prev}" in
	--run)
	    COMPREPLY=( $(compgen -W "B C D BC" -- ${cur}) )
            return 0
            ;;
	--mode)
	    # COMPREPLY=( $(compgen -W "DeriveThresholds DeriveThresholds_noDiJCut DeriveThresholds_inclSiMu_noDiJCut" -- ${cur}) )
	    local names=$(for x in `ls -1 /nfs/dust/cms/user/"$USER"/forBaconJets/2017PromptReco/Residuals/ | grep Run17BC[D]*_Data`; do y=${x#Run17[BC]*_Data_}; echo ${y#*_Data}; done)
	    COMPREPLY=( $(compgen -W "${names}" -- ${cur}) )
            return 0
            ;;
	--dname)
	    # COMPREPLY=( $(compgen -W "newPtBinning wMu17 wIsoMu27 wIsoMu20" -- ${cur}) )
	    local names=$(for x in `ls -1 /nfs/dust/cms/user/"$USER"/forBaconJets/2017PromptReco/Residuals/Run17*/ | grep Run17.*.root`; do k=${x%.root}; y=${k#Run17[BCD]*_Data_}; echo ${y#*_Data}; done)
	    COMPREPLY=( $(compgen -W "${names}" -- ${cur}) )
            return 0
            ;;
	--asym_cut)
	    COMPREPLY=( $(compgen -W "0.05" -- ${cur}) )
            return 0
            ;;
	--muTrg)
	    COMPREPLY=( $(compgen -W "HLT_Mu17 HLT_IsoMu20 HLT_IsoMu20" -- ${cur}) )
            return 0
            ;;
	--input)
	    COMPREPLY=( $(compgen -o filenames -f -- ${cur}) )
            return 0
            ;;	
        *)
        ;;
    esac
	
    if [[ ${cur} == -* ]] ; then
        COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
        return 0
    fi
}
complete -F _main ./main
