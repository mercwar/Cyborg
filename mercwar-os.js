/* ============================================================
   SYMSYS WINDOW MANAGER — DRAG, FOCUS, MIN/MAX/CLOSE
   ============================================================ */

let zCounter = 10;
let dragState = null;

function bringToFront(win) {
    zCounter++;
    win.style.zIndex = zCounter;
    document.querySelectorAll(".window").forEach(w => w.classList.remove("active"));
    win.classList.add("active");
}

function onTitleMouseDown(e) {
    const win = e.currentTarget.closest(".window");
    bringToFront(win);

    const rect = win.getBoundingClientRect();
    dragState = {
        win,
        startX: e.clientX,
        startY: e.clientY,
        startLeft: rect.left,
        startTop: rect.top
    };

    document.addEventListener("mousemove", onMouseMove);
    document.addEventListener("mouseup", onMouseUp);
}

function onMouseMove(e) {
    if (!dragState) return;

    const dx = e.clientX - dragState.startX;
    const dy = e.clientY - dragState.startY;

    dragState.win.style.left = dragState.startLeft + dx + "px";
    dragState.win.style.top = dragState.startTop + dy + "px";
}

function onMouseUp() {
    dragState = null;
    document.removeEventListener("mousemove", onMouseMove);
    document.removeEventListener("mouseup", onMouseUp);
}

function attachWindow(win) {
    const title = win.querySelector(".window-titlebar");
    title.addEventListener("mousedown", onTitleMouseDown);

    win.addEventListener("mousedown", () => bringToFront(win));

    const content = win.querySelector(".window-content");
    const btnMin = win.querySelector(".btn-min");
    const btnMax = win.querySelector(".btn-max");
    const btnClose = win.querySelector(".btn-close");

    btnMin.onclick = e => {
        e.stopPropagation();
        const isHidden = content.style.display === "none";
        content.style.display = isHidden ? "block" : "none";
    };

    btnMax.onclick = e => {
        e.stopPropagation();
        const max = win.dataset.max === "true";
        if (!max) {
            win.dataset.old = JSON.stringify({
                left: win.style.left,
                top: win.style.top,
                width: win.style.width,
                height: win.style.height
            });
            win.style.left = "4vw";
            win.style.top = "8vh";
            win.style.width = "92vw";
            win.style.height = "84vh";
            win.dataset.max = "true";
        } else {
            const old = JSON.parse(win.dataset.old);
            win.style.left = old.left;
            win.style.top = old.top;
            win.style.width = old.width;
            win.style.height = old.height;
            win.dataset.max = "false";
        }
    };

    btnClose.onclick = e => {
        e.stopPropagation();
        win.style.display = "none";
    };
}

document.querySelectorAll(".window").forEach(attachWindow);

/* ============================================================
   DROPDOWN WINDOW FOCUS
   ============================================================ */

const selector = document.getElementById("window-selector");
selector.addEventListener("change", () => {
    const id = selector.value;
    if (!id) return;
    const win = document.getElementById(id);
    if (!win) return;
    win.style.display = "block";
    bringToFront(win);
});
