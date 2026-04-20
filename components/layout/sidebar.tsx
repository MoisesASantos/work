"use client"

import Link from "next/link"
import { usePathname } from "next/navigation"
import { cn } from "@/lib/utils"
import { 
  Search, 
  Heart, 
  FileText, 
  MessageCircle, 
  Pill,
  LogOut,
  ChevronRight
} from "lucide-react"
import Image from "next/image"

const navItems = [
  { href: "/", label: "Explorar", icon: Search },
  { href: "/favoritos", label: "Favoritos", icon: Heart },
  { href: "/receitas", label: "Receitas", icon: FileText },
  { href: "/suporte", label: "Assistente IA", icon: MessageCircle },
]

export function SidebarContent() {
  const pathname = usePathname()

  return (
    <>
      <Link href="/landing" className="flex items-center gap-3 mb-10 px-2 pt-2 hover:opacity-80 transition-opacity">
        <div className="w-10 h-10 rounded-xl bg-primary flex items-center justify-center text-primary-foreground">
          <Pill className="w-5 h-5" />
        </div>
        <div>
          <h1 className="text-blue-900 dark:text-blue-400 text-sm font-black leading-tight font-serif">
            Digital Apothecary
          </h1>
          <p className="text-slate-500 text-[10px] uppercase tracking-wider">
            Luanda, AO
          </p>
        </div>
      </Link>

      <nav className="flex-1 space-y-1">
        {navItems.map((item) => {
          const isActive = pathname === item.href || 
            (item.href !== "/" && pathname.startsWith(item.href))
          const Icon = item.icon

          return (
            <Link
              key={item.href}
              href={item.href}
              className={cn(
                "flex items-center gap-3 px-4 py-3 rounded-lg transition-all duration-200",
                isActive
                  ? "bg-blue-50 dark:bg-blue-900/20 text-blue-900 dark:text-blue-300 font-bold"
                  : "text-slate-600 dark:text-slate-400 hover:bg-slate-100 dark:hover:bg-slate-800"
              )}
            >
              <Icon className="w-5 h-5" />
              <span className="font-medium">{item.label}</span>
            </Link>
          )
        })}
      </nav>

      {/* User Session Section */}
      <div className="pt-4 border-t border-border/15">
        <Link href="/perfil" className="flex items-center gap-3 p-3 rounded-xl hover:bg-slate-100 dark:hover:bg-slate-800 transition-all group">
          <div className="relative w-10 h-10 rounded-full overflow-hidden ring-2 ring-transparent group-hover:ring-primary/20 transition-all">
            <Image
              src="https://images.unsplash.com/photo-1472099645785-5658abf4ff4e?w=100&h=100&fit=crop&crop=face"
              alt="Foto de perfil"
              fill
              priority
              className="object-cover"
            />
          </div>
          <div className="flex-1 overflow-hidden">
            <p className="text-sm font-bold text-foreground truncate">João Silva</p>
            <p className="text-[11px] text-muted-foreground truncate">joao.silva@email.com</p>
          </div>
          <ChevronRight className="w-4 h-4 text-muted-foreground group-hover:text-primary transition-colors" />
        </Link>
      </div>
    </>
  )
}

export function Sidebar() {
  return (
    <aside className="fixed left-0 top-0 h-screen w-64 hidden md:flex flex-col border-r border-border/15 bg-slate-50 dark:bg-slate-950 z-50 p-4">
      <SidebarContent />
    </aside>
  )
}
