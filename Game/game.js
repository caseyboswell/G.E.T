class obstacle {
    constructor(type, ID) { //type 0: jump, type 1: duck
        this.type = type;
        this.ID = ID;
        this.blocker = null;
        
        this.createBlocker();
        document.getElementById("game").appendChild(this.blocker);
        this.alive = true;
        
        var that = this;
        setTimeout(this.deletes, 5000, this);
    }
    createBlocker(){
        var blocker = document.createElement("div");
        blocker.setAttribute('id', String(this.ID));
        
        if (this.type == 1){
            blocker.setAttribute('class', "block Stalactite");
        }else{
            blocker.setAttribute('class', "block Stalagmite");
        }
        
        this.blocker = blocker;
    }
    
    deletes(that){        
        document.getElementById(that.ID).remove();
        that.alive = false;
    }
    
    getConnect(){
        
    }
    getDist(){
        
    }
}

class charact{
    constructor(){
        this.state = "running";
        this.animateInterval = null;
        this.animate();
    }
    
    animate(){
        const frames = document.getElementById("character").children;
        console.log(frames);
        const frameCount = frames.length;
        let i = 0;
        this.animateInterval = setInterval(function (that) {
            frames[i % frameCount].style.display = "none";
            
            if (frames[(i+1) % frameCount].className.includes(that.state)){
                frames[++i % frameCount].style.display = "block";
            }else{
                while (! frames[(i+1) % frameCount].className.includes(that.state)){
                    i = i+1;
                };
                frames[++i % frameCount].style.display = "block";
            }
        }, 200, this);
    }
}

var obs = new charact()

var character = document.getElementById("character");
var block = document.getElementById("block");

var counter = 0;


function jump() {
    if(character.classList == "jump"){return}
    obs.state = "jumping";
    character.classList.add("jump");
    setTimeout(function(){
        character.classList.remove("jump");
        obs.state = "running";
    },1000);
}

function duck(){
    if(character.classList == "duck"){return}
    obs.state = "ducking";
    character.classList.add("duck");
    setTimeout(function(){
        character.classList.remove("duck");
        obs.state = "running";
    },1000);
}

function controller(e){
    
    if (e.key == "ArrowUp"){
        jump()
    }
    else if (e.key == "ArrowDown"){
        duck()
    }
}

document.addEventListener("keydown", controller);

var blockList = [];

SpawnBlock(0);

function SpawnBlock(count){
    var tim = 1000*((3*Math.E ** (-0.03*count) + 1)*Math.random() + 1);
    var type = Math.floor(2*Math.random());
    
    var obs = new obstacle(type, count);
    blockList.push(obs);
    
    console.log(blockList);
    
    setTimeout(SpawnBlock, tim, count+1);
}

var checkDead = setInterval(function() {
    var topBlock = blockList[0];
    
    if (topBlock.alive){
        blockBox = document.getElementById(topBlock.ID).getBoundingClientRect();
        charBox = document.getElementById("character").getBoundingClientRect();
        
        if (blockBox.left < charBox.left+charBox.width){
            if (topBlock.type){
                if(blockBox.bottom > charBox.top){
                    console.log("ahhhhh")
                }
            }
            else{
                if(charBox.bottom > blockBox.top){
                    console.log("ahhhhh")
                }
            }
        }
        
    }else{
        blockList.shift();
    }
    
    /*
    let characterTop = parseInt(window.getComputedStyle(character).getPropertyValue("bottom"));
    let blockLeft = parseInt(window.getComputedStyle(block).getPropertyValue("left"));
    let blockHight = parseInt(window.getComputedStyle(block).getPropertyValue("bottom")) + 
                        parseInt(window.getComputedStyle(block).getPropertyValue("height"));
    
    console.log(characterTop <= blockHight);
    
    if(blockLeft < 20 && blockLeft > -20 && characterTop <= blockHight){
        console.log("dead");
        block.style.animation = "none";
        //alert("Game Over. score: "+Math.floor(counter/100));
        counter = 0;
        block.style.animation = "block 5s infinite linear";
    }else{
        counter++;
        document.getElementById("scoreSpan").innerHTML = Math.floor(counter/100);
    }*/
}, 10);