

def Yes_No_Question(question):
   """ Function that asks a question and excepts yes or no as an answerself.
       Will return true if answer include 'Y', 'y', or is blankself.
       Will return false if answer includes 'N' or 'n'.
       Will ask again if answer doesn't fit any above cases. """
   inp = str(input(question + ' [Y/N]: '))
   if ('y' in inp or 'Y' in inp or inp == ''):
      return True
   elif ('n' in inp or 'N' in inp):
      return False
   else:
      print('Enter valid answer.')
      return Yes_No_Question(question)
   # end if
# end def
