Set args = Wscript.Arguments
Set voice = CreateObject("SAPI.SpVoice")
voice.Rate = 1
voice.Volume = 100
Say = args(0)
If (Len(Say) > 0) Then
    voice.Speak Say
End If 
