
// Put all onload AJAX calls here, and event listeners

// let files= [];
// $.ajax({

//     type: 'get',            //Request type
//         dataType: 'file',       //Data type - we will use JSON for almost everything 
//         url: '/upload/:name',   //The server endpoint we are connecting to
//         data: {
//             "name": "quad01.svg"
//         },

//         success: function(data){
//             console.log(data);
//         },
//         fail: function(error){
//             console.log(error);
//             alert("Failed to fetch server");
//         }
// });


var names=[];

jQuery(document).ready(function() {

    // On page-load AJAX Example
    jQuery.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/foldercontents',   //The server endpoint we are connecting to
        data: {
            
        },
        success: function (data) {
            /*  Do something with returned object
            Note that what we get is an object, not a string, 
            so we do not need to parse it on the server.
            JavaScript really does handle JSONs seamlessly
            */
           // jQuery('#blah').html("On page load, received string '"+data.somethingElse+"' from server");
           //We write the object to the console to show that the request was successful
           // console.log(data,"data"); 
           // names=data;
           // console.log(names);
           data.forEach((element) => {
               // console.log(element,"why");
               
               if(element.name.includes('.svg')){
                   
                   names.push(element);
                   
                }
                
            }); 
            $("#imgSi").attr('src', 'uploads/' + names[0].name)
            console.log(names[0].name,'fffsdfsdf');
            let file = names[0];
            console.log(file,'ffff');
            let $tit =$(
                `
                <td contenteditable='true' class='clear width'>
                ${file.title}
                </td>
                `
            )
            $tit.appendTo($("#title"))
    
            let $desc =$(
                `
                <td contenteditable='true' class='clear width'>
                ${file.desc}
                </td>
                `
            )
            $desc.appendTo($("#desc"))
            file.rectList.forEach((rect,index)=>{
                let $RectFile =$(
                        `<tr class="clear">
                            <td>Rectangle ${index + 1}
                            </td>
                            <td>Upper left corner: x :${rect.x}${rect.units} , y:${rect.y}${rect.units},<br/>
                                width: ${rect.w}${rect.units} , height: ${rect.h}${rect.units} 
                            </td>
                            <td> ${rect.numAttr}
                            </td>
    
                        </tr>`
                    )
                    $RectFile.appendTo($("#properties"))
    
            });
    
            file.circList.forEach((circ,index)=>{
                let $CircFile =$(
                        `<tr class="clear">
                            <td>Circle ${index + 1}
                            </td>
                            <td>Centre: x :${circ.cx}${circ.units} , y:${circ.cy}${circ.units},<br/>
                                radius: ${circ.r}${circ.units} 
                            </td>
                            <td> ${circ.numAttr}
                            </td>
    
                        </tr>`
                    )
                    $CircFile.appendTo($("#properties"))
    
            });
            
            // console.log(pathList);
            file.pathList.forEach((path,index)=>{
                let $PathFile =$(
                        `<tr class="clear">
                            <td>Path ${index +1}
                            </td>
                            <td> d :${path.d}
                            </td>
                            <td> ${path.numAttr}
                            </td>
    
                        </tr>`
                    )
                    $PathFile.appendTo($("#properties"))
    
            });
    
            file.groupList.forEach((grp,index)=>{
                let $GroupFile =$(
                        `<tr class="clear">
                            <td>Group ${index + 1}
                            </td>
                            <td> children :${grp.children}
                            </td>
                            <td> ${grp.numAttr}
                            </td>
    
                        </tr>`
                    )
                    $GroupFile.appendTo($("#properties"))
    
            });
           

for(let file of names){
   
    let $fileLogPannel =$(
    `<tr>
        <td>
            <a href=${file.name} download = ${file.name}>
            <img src=${file.name} class="Fileinfo" id="imgS">
            </a> 
        </td>
        <td>
            <a href=${file.name} download = ${file.name}>
            ${file.name}
            </a>
        </td>
        <td>
            ${file.size}
        </td>
        <td>
            ${file.rects}
        </td>
        <td>
            ${file.circs}
        </td>
        <td>
            ${file.paths}
        </td>
        <td>
            ${file.grps}
        </td>
    </tr>
    `
     )
     $fileLogPannel.appendTo($("#panel"))

}

for(let file of names){
    $('#file-options').append(
        $('<option/>')
     
        .text(file.name)
    );
    
}
for(let file of names){
    $('#file-form').append(
        $('<option/>')
        
        .text(file.name)
    );
    
}
for(let file of names){
    $('#file-scale').append(
        $('<option/>')
     
        .text(file.name)
    );
    
}

$('#rectcirc').append(
    $('<option/>')

    .text("Rectangle")
);
$('#rectcirc').append(
    $('<option/>')
    //
    .text("Circle")
);

$('#RCscale').append(
    $('<option/>')
    
    .text("Rectangle")
);
$('#RCscale').append(
    $('<option/>')

    .text("Circle")
);
$('#createAdd').append(
    $('<button/>')
    .text("Add ")
);
let scaling=$(
    `
    <tr>
    <td><label name="Rectangle">Rectangle  :</label></td>
    <td><input type="text" name="rect" value="1"></td>
    </tr>
    <tr>
    <td><label name="Circle">Circle  :</label></td>
    <td><input type="text" name="circ" value="1"></td>
    <td><input type="submit" name="btn" value="Submit"></td>    
    </tr>
    `
)
scaling.appendTo($("#scale"))
    
           
        },
        fail: function(error) {
            // Non-200 return, do something with error
            $('#blah').html("On page load, received error from server");
            console.log(error); 
        }
    });



    $(document).on("change","#rectcirc",function(){
        $('.shapeClear').each(function () {
            $(this).remove();
        });
    
        console.log($(this).val());
        if ($(this).val() === 'Rectangle') {
            console.log('rect working');
       

            let rectShape= $(
                `
                
                <tr class ="shapeClear">
                    <td><label name="x">x  :</label></td>
                    <td><input type="text" name="x" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label name="y">y  :</label></td>
                    <td><input type="text" name="y" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label>width  :</label></td>
                    <td><input type="text" name="width" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label>height  :</label></td>
                    <td><input type="text" name="height" value="1cm"></td>
                </tr>
             
                `
            )
            rectShape.appendTo($("#Shape"))
            let $Btnn = $(
                `
                <button class="shapeClear">Submit</button>
                `
            )
            $Btnn.appendTo($("#Shape"))     
       
        } 
        else if ($(this).val() === 'Circle') {
         
            let circShape= $(
                `
                
                <tr class ="shapeClear">
                    <td><label>cx  :</label></td>
                    <td><input type="text" name="cx" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label >cy  :</label></td>
                    <td><input type="text" name="cy" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label>r  :</label></td>
                    <td><input type="text" name="r" value="1cm"></td>
                </tr>
                
                `
            )
            circShape.appendTo($("#Shape"))
            let $Btnn = $(
                `
                <button class="shapeClear">Submit</button>
                `
            )
            $Btnn.appendTo($("#Shape")) 

        }

    });



    $(document).on("change","#file-options",function(){
        $('#imgSi')
        .attr("src", $("#file-options option:selected").text());
        $('.clear').each(function () {
            $(this).remove();
        });
        $('.clean').each(function () {
            $(this).remove();
        });
        let file = getfile('#file-options');
        // console.log(file.desc,"dds");

        let $tit =$(
            `
            <td contenteditable='true' class='clear width'>
            ${file.title}
            </td>
            `
        )
        $tit.appendTo($("#title"))

        let $desc =$(
            `
            <td contenteditable='true' class='clear width'>
            ${file.desc}
            </td>
            `
        )
        $desc.appendTo($("#desc"))

        console.log("file");
        console.log(file);
        file.rectList.forEach((rect,index)=>{
            let $RectFile =$(
                    `<tr class="clear">
                        <td>Rectangle ${index + 1}
                        </td>
                        <td>Upper left corner: x :${rect.x}${rect.units} , y:${rect.y}${rect.units},<br/>
                            width: ${rect.w}${rect.units} , height: ${rect.h}${rect.units} 
                        </td>
                        <td> ${rect.numAttr}
                        </td>

                    </tr>`
                )
                $RectFile.appendTo($("#properties"))

        });

        file.circList.forEach((circ,index)=>{
            let $CircFile =$(
                    `<tr class="clear">
                        <td>Circle ${index + 1}
                        </td>
                        <td>Centre: x :${circ.cx}${circ.units} , y:${circ.cy}${circ.units},<br/>
                            radius: ${circ.r}${circ.units} 
                        </td>
                        <td> ${circ.numAttr}
                        </td>

                    </tr>`
                )
                $CircFile.appendTo($("#properties"))

        });
        
        // console.log(pathList);
        file.pathList.forEach((path,index)=>{
            let $PathFile =$(
                    `<tr class="clear">
                        <td>Path ${index +1}
                        </td>
                        <td> d :${path.d}
                        </td>
                        <td> ${path.numAttr}
                        </td>

                    </tr>`
                )
                $PathFile.appendTo($("#properties"))

        });

        file.groupList.forEach((grp,index)=>{
            let $GroupFile =$(
                    `<tr class="clear">
                        <td>Group ${index + 1}
                        </td>
                        <td> children :${grp.children}
                        </td>
                        <td> ${grp.numAttr}
                        </td>
                    </tr>`
                )
                $GroupFile.appendTo($("#properties"))

        });
       
        
    });

    $(document).on("click","#hide_attr",function(){
        $('.clean').each(function () {
            $(this).remove();
        });
    });


    $(document).on("click","#btn",function(){
        $('.clean').each(function () {
            $(this).remove();
        });
        let $hide_btn =$(
            `
            <button class="clean">Hide Attributes</button>
            `
        )
        $hide_btn.appendTo($("#hide_attr"))
        let file = getfile('#file-options');



        let $SVGatr =$(
            `<tr class="clean">
                <th >SVG 
                </th>
                <th>NAME
                </th>
                <th>VALUE
                </th>
            </tr>`
        )
        $SVGatr.appendTo($("#pp"))

        file.svgAttr.forEach((atr,count)=>{
            console.log(count);
            let $svgFile =$(
                `
                <tr class="clean">
                <td>
                </td>
                <td contenteditable='true'>${atr.name} 
                </td>
                <td contenteditable='true'>${atr.value}
                </td>
                </tr>
                `
            )
            $svgFile.appendTo($("#pp"))
        });

            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))

        file.rectList.forEach((rect,count)=>{
            console.log(count,'insidelist');
            let $RectFile =$(
                `<tr class="clean">
                    <th >Rectangle ${count + 1}
                    </th>
                    <th>NAME
                    </th>
                    <th>VALUE
                    </th>
                </tr>`
            )
            $RectFile.appendTo($("#pp"))

            let $RectRequired = $(
                `
                <tr class="clean">
                <td>
                </td>
                <td>x 
                </td>
                <td contenteditable='true'>${rect.x}${rect.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>y 
                </td>
                <td contenteditable='true'>${rect.y}${rect.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>width 
                </td>
                <td contenteditable='true'>${rect.w}${rect.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>height 
                </td>
                <td contenteditable='true'>${rect.h}${rect.units}
                </td>
                </tr>
                `
            )
            $RectRequired.appendTo($("#pp"))

            file.rectAttr[count].forEach((atr,index2)=>{
                console.log(count,'insideAttr');
                let $rectAtr = $(
                    `<tr class="clean">
                    <td>
                    </td>
                    <td contenteditable='true'>${atr.name} 
                    </td>
                    <td contenteditable='true'>${atr.value}
                    </td>
                    </tr>
                    `
                )
                $rectAtr.appendTo($("#pp"))
            });

            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))

        });

        file.circList.forEach((circ,count)=>{
            console.log(count);
            let $CircFile =$(
                `<tr class="clean">
                    <th >Circle ${count + 1}
                    </th>
                    <th>NAME
                    </th>
                    <th>VALUE
                    </th>
                </tr>`
            )
            $CircFile.appendTo($("#pp"))

            let $CircRequired = $(
                `
                <tr class="clean">
                <td>
                </td>
                <td>cx 
                </td>
                <td contenteditable='true'>${circ.cx}${circ.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>y 
                </td>
                <td contenteditable='true'>${circ.cy}${circ.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>r 
                </td>
                <td contenteditable='true'>${circ.r}${circ.units}
                </td>
                </tr>
                `
            )
            $CircRequired.appendTo($("#pp"))

            file.circAttr[count].forEach((atr,index2)=>{
                let $circAtr = $(
                    `<tr class="clean">
                    <td>
                    </td>
                    <td contenteditable='true'>${atr.name} 
                    </td>
                    <td contenteditable='true'>${atr.value}
                    </td>
                    </tr>
                    `
                )
                $circAtr.appendTo($("#pp"))
            });
            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))


        });
        file.pathList.forEach((path,count)=>{
            console.log(count);
            let $PathFile =$(
                `<tr class="clean">
                    <th >Path ${count + 1}
                    </th>
                    <th>NAME
                    </th>
                    <th>VALUE
                    </th>
                </tr>`
            )
            $PathFile.appendTo($("#pp"))

            let $PathRequired = $(
                `
                <tr class="clean">
                <td>
                </td>
                <td>data 
                </td>
                <td contenteditable='true'>${path.d}
                </td>
                </tr>
                `
            )
            $PathRequired.appendTo($("#pp"))

            file.pathAttr[count].forEach((atr,index2)=>{
                let $pathAtr = $(
                    `<tr class="clean">
                    <td>
                    </td>
                    <td contenteditable='true'>${atr.name} 
                    </td>
                    <td contenteditable='true'>${atr.value}
                    </td>
                    </tr>
                    `
                )
                $pathAtr.appendTo($("#pp"))
            });
            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))


        });
        file.groupList.forEach((group,count)=>{
            console.log(count);
            let $GroupFile =$(
                `<tr class="clean">
                    <th >Group ${count + 1}
                    </th>
                    <th>NAME
                    </th>
                    <th>VALUE
                    </th>
                </tr>`
            )
            $GroupFile.appendTo($("#pp"))

            file.groupAttr[count].forEach((atr,index2)=>{
                let $GroupAtr = $(
                    `<tr class="clean">
                    <td>
                    </td>
                    <td contenteditable='true'>${atr.name} 
                    </td>
                    <td contenteditable='true'>${atr.value}
                    </td>
                    </tr>
                    `
                )
                $GroupAtr.appendTo($("#pp"))
            });
            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))


        });

    });


    $(document).on('click', '.displayAtr', function () {
        let temp = $(this);
        $(`<tr class="clean">
                <td></td>
                <td contenteditable="true">Attribute</td>
                <td contenteditable="true">Value</td>
            </tr>`).insertBefore(temp);
    });


   

    function getfile(id){
        let bitch = $(id + " option:selected").text();
        for(let file of names){
            if(file.name == bitch){
                return file;
            }
        }
        return file[0];
    }


    let Createsvg=$(
        `
        <tr>
        <td><label name="createsvg">File Name  :</label></td>
        <td><input type="text" name="vreate" value=""></td>
        </tr>
        <tr>
        <td><label name="title">title  :</label></td>
        <td><input type="text" name="tit" value=""></td>
        </tr>
        <tr>
        <td><label name="description">description  :</label></td>
        <td><input type="text" name="desc" value=""></td>
        </tr>
        <tr >
        <td><input type="submit" name="create" value="Create SVG"></td>    
        <td ><input type="button" id="renu" value="Add Shape"></input></td>    
        </tr>
        </tr>
        `
    )
    Createsvg.appendTo($("#svg"))

    $(document).on("click","#hide_atr",function(){
        $('.clean_SVG').each(function () {
            $(this).remove();
        });
    });

    $(document).on("click","#renu",function(){
        $('.clean_SVG').each(function () {
            $(this).remove();
        });
   
        let rc = $(
            `
            <tr class="clean_SVG">
            <td><button type="button" id="createrect">RECTANGLE</button></td>
            </tr>
            <tr class="clean_SVG">
            <td><button type="button" id="createcirc">CIRCLE</button></td>
            </tr>
            `
        )
        rc.appendTo($("#renuMain"))
    });

    $(document).on('click', '#renu', function ()
    {
        // var elem = document.getElementById("renu");
    if (this.value=="Add Shape") {
        this.value = "Hide";
        this.id = "hide_renu";
    
    }
    else{

        this.value = "Add Shape";
        this.id ="renu";
    }
        
    });
    $(document).on("click","#hide_renu",function(){
        $('.clean_SVG').each(function () {
            $(this).remove();
        });
        if (this.value=="Hide") {
            this.value = "Add Shape";
            this.id ="renu";
            
        
        }
        else{
            
            this.value = "Hide";
            this.id = "hide_renu";
        }
        // this.id ="renu";
    });

    $(document).on('click', '#createrect', function () {
        let temp = $(this);
        $(`
        <tr class="clean_SVG">
        <th>Rectangle</th>
        </tr>
        <tr class="clean_SVG">
                    <td><label name="x">x  :</label></td>
                    <td><input type="text" name="x" value="1cm"></td>
                </tr>
                <tr class="clean_SVG">
                    <td><label name="y">y  :</label></td>
                    <td><input type="text" name="y" value="1cm"></td>
                </tr>
                <tr class="clean_SVG">
                    <td><label>width  :</label></td>
                    <td><input type="text" name="width" value="1cm"></td>
                </tr>
                <tr class="clean_SVG">
                    <td><label>height  :</label></td>
                    <td><input type="text" name="height" value="1cm"></td>
                </tr>
                <tr class="clean_SVG">
                <td></td>
                <td><input type="button" name="height" value="Submit"></td>
            </tr>    
        `).insertAfter(temp);
    });
    $(document).on('click', '#createcirc', function () {
       
        
        let temp = $(this);
        $(`  
        <tr class="clean_SVG">
        <th>Circle</th>
           </tr>     
        <tr class="clean_SVG">
            <td><label>cx  :</label></td>
            <td><input type="text" name="cx" value="1cm"></td>
        </tr>
        <tr class="clean_SVG">
            <td><label >cy  :</label></td>
            <td><input type="text" name="cy" value="1cm"></td>
        </tr>
        <tr class="clean_SVG">
            <td><label>r  :</label></td>
            <td><input type="text" name="r" value="1cm"></td>
        </tr>
        <tr class="clean_SVG">
        <td></td>
        <td><input type="button" name="height" value="Submit"></td>
    </tr>
        
    
       
        `).insertAfter(temp);
    });

        
    



    // Event listener form example , we can use this instead explicitly listening for events
    // No redirects if possible
    $('#someform').submit(function(e){
        $('#blah').html("Form has data: "+$('#entryBox').val());
        e.preventDefault();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
        });
    });


});

