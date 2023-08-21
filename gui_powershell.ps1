Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
Add-Type -Path "C:\Users\PARDIS\Desktop\uni\2nd term\advanced programing\project_new\main.c" -Language C

# Create form
$form = New-Object System.Windows.Forms.Form
$form.Text = "Image Processing Program"
$form.Width = 400
$form.Height = 250
$form.StartPosition = "CenterScreen"
$form.FormBorderStyle = "FixedDialog"
$form.MaximizeBox = $false

# Create label for input selection
$lblInput = New-Object System.Windows.Forms.Label
$lblInput.Text = "Please choose your input method:"
$lblInput.Width = 200
$lblInput.Height = 20
$lblInput.Location = New-Object System.Drawing.Point(10, 10)
$form.Controls.Add($lblInput)

# Create radio buttons for input selection
$rdoPath = New-Object System.Windows.Forms.RadioButton
$rdoPath.Text = "Path in PC"
$rdoPath.Location = New-Object System.Drawing.Point(10, 30)
$rdoPath.Checked = $true
$form.Controls.Add($rdoPath)

$rdoURL = New-Object System.Windows.Forms.RadioButton
$rdoURL.Text = "URL"
$rdoURL.Location = New-Object System.Drawing.Point(10, 50)
$form.Controls.Add($rdoURL)

$rdoEmail = New-Object System.Windows.Forms.RadioButton
$rdoEmail.Text = "Email"
$rdoEmail.Location = New-Object System.Drawing.Point(10, 70)
$form.Controls.Add($rdoEmail)

# Create OK button
$btnOK = New-Object System.Windows.Forms.Button
$btnOK.Text = "OK"
$btnOK.Width = 75
$btnOK.DialogResult = [System.Windows.Forms.DialogResult]::OK
$btnOK.Location = New-Object System.Drawing.Point(200, 200)
$form.Controls.Add($btnOK)

# Create event handler for OK button
$btnOK.Add_Click({
    $inputMethod = ""
    if ($rdoPath.Checked) {
        $inputMethod = "path"
    }
    elseif ($rdoURL.Checked) {
        $inputMethod = "url"
    }
    elseif ($rdoEmail.Checked) {
        $inputMethod = "email"
    }

    if ($inputMethod -eq "path") {
        $openFileDialog = New-Object System.Windows.Forms.OpenFileDialog
        $openFileDialog.Filter = "Image Files (*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp|All files (*.*)|*.*"
        $openFileDialog.Title = "Select an image file"
        if ($openFileDialog.ShowDialog() -eq [System.Windows.Forms.DialogResult]::OK) {
            $input = $openFileDialog.FileName
            $imageFormat = ShowImageFormatDialog(nothing)
            if ($imageFormat -eq "bmp") {
                bmp($input)
            }
            elseif ($imageFormat -eq "png") {
                png($input)
            }
            elseif ($imageFormat -eq "jpg") {
                jpg($input)
            }
        }
    }
    elseif ($inputMethod -eq "url") {
        $input = ShowInputDialog("Please enter the URL of the image:")
        $imageFormat = ShowImageFormatDialog(nothing)
        if ($imageFormat -eq "bmp") {
            bmp($input)
        }
        elseif ($imageFormat -eq "png") {
            png($input)
        }
        elseif ($imageFormat -eq "jpg") {
            jpg($input)
        }
    }
    elseif ($inputMethod -eq "email") {
        # fetch email
        fetchemail

        # fetch txt extract to img decode txt
        extractdecodetxt

        # decoding sex
        decodefetchtxttoimg
    }
})

# Create function to show image format selection dialog
function ShowImageFormatDialog() {
    $dialog = New-Object System.Windows.Forms.Form
    $dialog.Text = "Select Image Format"
    $dialog.Width = 200
    $dialog.Height = 150
    $dialog.StartPosition = "CenterScreen"
    $dialog.FormBorderStyle = "FixedDialog"
    $dialog.MaximizeBox = $false

    # Create label for format selection
    $lblFormat = New-Object System.Windows.Forms.Label
    $lblFormat.Text = "Please choose your image format:"
    $lblFormat.Width = 200
    $lblFormat.Height = 20
    $lblFormat.Location = New-Object System.Drawing.Point(10, 10)
    $dialog.Controls.Add($lblFormat)

    # Create radio buttons for image format selection
    $rdoJPG = New-Object System.Windows.Forms.RadioButton
    $rdoJPG.Text = "JPG or JPEG"
    $rdoJPG.Location = New-Object System.Drawing.Point(10, 30)
    $rdoJPG.Checked = $true
    $dialog.Controls.Add($rdoJPG)

    $rdoPNG = New-Object System.Windows.Forms.RadioButton
    $rdoPNG.Text = "PNG"
    $rdoPNG.Location = New-Object System.Drawing.Point(10, 50)
    $dialog.Controls.Add($rdoPNG)

    $rdoBMP = New-Object System.Windows.Forms.RadioButton
    $rdoBMP.Text = "Bitmap"
    $rdoBMP.Location = New-Object System.Drawing.Point(10, 70)
    $dialog.Controls.Add($rdoBMP)

    # Create OK button
    $btnOK = New-Object System.Windows.Forms.Button
    $btnOK.Text = "OK"
    $btnOK.Width = 75
    $btnOK.DialogResult = [System.Windows.Forms.DialogResult]::OK
    $btnOK.Location = New-Object System.Drawing.Point(50, 100)
    $dialog.Controls.Add($btnOK)

    # Create event handler for OK button
    $btnOK.Add_Click({
        if ($rdoJPG.Checked) {
            $format = "jpg"
        }
        elseif ($rdoPNG.Checked) {
            $format = "png"
        }
        elseif ($rdoBMP.Checked) {
            $format = "bmp"
        }
        $dialog.DialogResult = $format
    })

    # Show dialog and return selected format
    $result = $dialog.ShowDialog()
    if ($result -eq [System.Windows.Forms.DialogResult]::OK) {
        return $dialog.DialogResult
    }
}

# Create function to show input dialog
function ShowInputDialog($message) {
    $dialog = New-Object System.Windows.Forms.Form
    $dialog.Text = "Input url"
    $dialog.Width = 300
    $dialog.Height = 150
    $dialog.StartPosition = "CenterScreen"
    $dialog.FormBorderStyle = "FixedDialog"
    $dialog.MaximizeBox = $false

    # Create label for message
    $lblMessage = New-Object System.Windows.Forms.Label
    $lblMessage.Text = $message
    $lblMessage.Width = 300
    $lblMessage.Height = 20
    $lblMessage.Location = New-Object System.Drawing.Point(10, 10)
    $dialog.Controls.Add($lblMessage)

    # Create text box for input
    $txtInput = New-Object System.Windows.Forms.TextBox
    $txtInput.Width = 200
    $txtInput.Location = New-Object System.Drawing.Point(10, 40)
    $dialog.Controls.Add($txtInput)

    # Create OK button
    $btnOK = New-Object System.Windows.Forms.Button
    $btnOK.Text = "OK"
    $btnOK.Width = 75
    $btnOK.DialogResult = [System.Windows.Forms.DialogResult]::OK
    $btnOK.Location = New-Object System.Drawing.Point(50, 80)
    $dialog.Controls.Add($btnOK)

    # Create event handler for OK button
    $btnOK.Add_Click({
        $dialog.DialogResult = $txtInput.Text
    })

    # Show dialog and return input
    $result = $dialog.ShowDialog()
    if ($result -eq [System.Windows.Forms.DialogResult]::OK) {
        return $dialog.DialogResult
    }
}

# Show form and wait for user input
$result = $form.ShowDialog()
if ($result -eq [System.Windows.Forms.DialogResult]::OK) {
    # Call appropriate function based on input method and image format
    $inputMethod = $result[0]
    if ($inputMethod -eq "path") {
        $input = $result[1]
        $imageFormat = $result[2]
        if ($imageFormat -eq "bmp") {
            bmp($input)
        }
        elseif ($imageFormat -eq "png") {
            png($input)
        }
        elseif ($imageFormat -eq "jpg") {
            jpg($input)
        }
    }
    elseif ($inputMethod -eq "url") {
        $input = $result[1]
        $imageFormat = $result[2]
        if ($imageFormat -eq "bmp") {
            bmp($input)
        }
        elseif ($imageFormat -eq "png") {
            png($input)
        }
        elseif ($imageFormat -eq "jpg") {
            jpg($input)
        }
    }
    elseif ($inputMethod -eq "email") {
        # fetch email
        fetchemail

        # fetch txt extract to img decode txt
        extractdecodetxt

        # decoding sex
        decodefetchtxttoimg
    }
Q}