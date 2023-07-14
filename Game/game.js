class obstacle {
    constructor(type, ID) { //type 0: jump, type 1: duck
        this.type = type;
        this.ID = ID;
        this.blocker = null;
        
        this.createBlocker();
        document.getElementById("blockers").appendChild(this.blocker);
        this.alive = true;
        
        var that = this;
        setTimeout(this.deletes, 5000, this);
    }
    createBlocker(){
        var blocker = document.createElement("div");
        blocker.setAttribute('id', String(this.ID));
        
        if (this.type == 1){
            blocker.setAttribute('class', "block StalactiteWrapper Stalactite");
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
        console.log(this.blocker.style.left);
    }
}

class charact{
    constructor(){
        this.state = "running";
        this.animateInterval = null;
        this.animate();
        
        this.duck = false;
        this.jump = false;
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

function duck() {
    if(character.classList == "duck"){return}
    obs.state = "ducking";
    character.classList.add("duck");
    setTimeout(function(){
        character.classList.remove("duck");
        obs.state = "running";
    },1000);
}

function controller(e){
    
    if (e.key == "ArrowUp" || e == "squat"){
        obs.jump = true; //jump()
    }
    else if (e.key == "ArrowDown" || e == "pushup"){
        obs.duck = true; //duck()
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
    
    setTimeout(SpawnBlock, tim, count+1);
}

var checkDead = setInterval(function() {
    var topBlock = blockList[0];
    
    if (topBlock.alive){
        blockBox = topBlock.blocker.getBoundingClientRect();
        charBox = document.getElementById("character").getBoundingClientRect();
        
        if (blockBox.left < charBox.left+charBox.width){
            if (topBlock.type){
                if(blockBox.bottom > charBox.top){
                    if (obs.duck == true){
                        duck();
                        obs.duck = false;
                    }
                    else{
                        console.log("ahhhhh")
                    }
                }
            }
            else{
                if(charBox.bottom > blockBox.top){
                    if (obs.jump == true){
                        jump();
                        obs.jump = false;
                    }
                    else{
                        console.log("ahhhhh")
                    }
                }
            }
        }
        
    }else{
        blockList.shift();
    }
}, 10);